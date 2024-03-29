/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>
#include <algorithm>
#include <unordered_set>

#include "common/defs.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/record/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/index.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"

const static int IDNEX_HEADER_NUM = 5;
const static char *INDEX_HEADER[] = {"Table", "Non_unique", "Key_name", "Seq_in_index", "Column_name"};

Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (std::vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(
    const char *path, const char *name, const char *base_dir, int attribute_count, const AttrInfo attributes[], CLogManager *clog_manager)
{

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p", name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm = BufferPoolManager::instance();
  rc = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

 for (size_t i=0; i < attribute_count; i++) {
  if (attributes[i].type == AttrType::TEXTS) {
    // 存在TEXT类型字段，创建text数据文件
    std::string text_data_file = table_text_file(base_dir, name);
    rc = bpm.create_file(text_data_file.c_str());
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create disk buffer pool of text data file. file name=%s", text_data_file.c_str());
      return rc;
    }
    break;
  } 
 }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;
  clog_manager_ = clog_manager;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}


RC Table::drop() {

  sync();

  const char *dir = base_dir_.c_str();

  // 1. 删除描述表元数据的文件
  // 1.1 获取表元数据文件路径
  std::string table_file_path = table_meta_file(dir, name());
  LOG_INFO("table_file_path = %s", table_file_path.c_str());
  // 1.2 调用remove()删除文件
  if (unlink(table_file_path.c_str()) != 0) {
    LOG_ERROR("Failed to remove meta file = %s, errno = %s", table_file_path.c_str(), errno);
    return RC::GENERIC_ERROR;
  }

  // 2. 删除数据文件
  // 2.1 获取数据文件路径
  std::string table_data_path = table_data_file(dir, name());
  // 2.2 调用remove()删除文件
  if (unlink(table_data_path.c_str()) != 0) {
    LOG_ERROR("Failed to remove data file = %s, errno = %s", table_data_path.c_str(), errno);
    return RC::GENERIC_ERROR;
  }

  // 3. 删除索引
  // 3.1 遍历删除索引
  for (auto index: indexes_) {
    ((BplusTreeIndex*)index)->close();
    // 3.2 获取索引文件路径
    std::string table_index_path = table_index_file(dir, name(), index->index_meta().name()); 
    // 3.3 调用remove()删除文件
    if (unlink(table_index_path.c_str()) != 0) {
      LOG_ERROR("Failed to remove index file = %s, errno = %s", table_index_path.c_str(), errno);
      return RC::GENERIC_ERROR;
    }
  }

  // 4. 删除text数据文件
  if (text_buffer_pool_ != nullptr) {
    std::string text_data_path = table_text_file(dir, name());
    if (unlink(text_data_path.c_str()) != 0) {
      LOG_ERROR("Failed to remove data file = %s, errno = %s", text_data_path.c_str(), errno);
      return RC::GENERIC_ERROR;
    }
  }
  return RC::SUCCESS;
}


RC Table::open(const char *meta_file, const char *base_dir, CLogManager *clog_manager)
{
  // 加载元数据文件
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (size_t i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const std::vector<std::string> fields = index_meta->fields();
    for (auto field: fields) {
      const FieldMeta *field_meta = table_meta_.field(field.c_str());
      if (field_meta == nullptr) {
        LOG_ERROR("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
            name(),
            index_meta->name(),
            field.c_str());
        // skip cleanup
        //  do all cleanup action in destructive Table function
        return RC::GENERIC_ERROR;
      }
    }
    // TODO(vanish): Multi-index 暂时只取一个field_meta，后面需要修改index模块下内容
    const FieldMeta *field_meta = table_meta_.field(fields[0].c_str());

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = table_index_file(base_dir, name(), index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, *field_meta);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
          name(),
          index_meta->name(),
          index_file.c_str(),
          rc,
          strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  if (clog_manager_ == nullptr) {
    clog_manager_ = clog_manager;
  }
  return rc;
}

RC Table::commit_insert(Trx *trx, const RID &rid)
{
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get record %s: %s", this->name(), rid.to_string().c_str());
    return rc;
  }

  return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid)
{

  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get record %s: %s", this->name(), rid.to_string().c_str());
    return rc;
  }

  // remove all indexes
  rc = delete_entry_of_indexes(record.data(), rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d) while rollback insert, rc=%d:%s",
        rid.page_num,
        rid.slot_num,
        rc,
        strrc(rc));
    return rc;
  }

  rc = record_handler_->delete_record(&rid);
  return rc;
}

RC Table::insert_record(Trx *trx, Record *record)
{
  RC rc = RC::SUCCESS;

  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }
  rc = record_handler_->insert_record(record->data(), table_meta_.record_size(), &record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->insert_record(this, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(insertion) to trx");

      RC rc2 = record_handler_->delete_record(&record->rid());
      if (rc2 != RC::SUCCESS) {
        LOG_ERROR("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
            name(),
            rc2,
            strrc(rc2));
      }
      return rc;
    }
  }

  rc = insert_entry_of_indexes(record->data(), record->rid());
  if (rc != RC::SUCCESS) {
    RC rc2 = delete_entry_of_indexes(record->data(), record->rid(), true);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
          name(),
          rc2,
          strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record->rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
          name(),
          rc2,
          strrc(rc2));
    }
    return rc;
  }

  if (trx != nullptr) {
    // append clog record
    CLogRecord *clog_record = nullptr;
    rc = clog_manager_->clog_gen_record(CLogType::REDO_INSERT, trx->get_current_id(), clog_record, name(), table_meta_.record_size(), record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a clog record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
    rc = clog_manager_->clog_append_record(clog_record);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  return rc;
}

RC Table::recover_insert_record(Record *record)
{
  RC rc = RC::SUCCESS;

  rc = record_handler_->recover_insert_record(record->data(), table_meta_.record_size(), &record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  return rc;
}

RC Table::recover_update_record(Record *record) {
  RC rc = RC::SUCCESS;

  rc = record_handler_->recover_insert_record(record->data(), table_meta_.record_size(), &record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  return rc;  
}

RC Table::insert_record(Trx *trx, int value_num, const Value *values)
{
  if (value_num <= 0 || nullptr == values) {
    LOG_ERROR("Invalid argument. table name: %s, value num=%d, values=%p", name(), value_num, values);
    return RC::INVALID_ARGUMENT;
  }
  
  char *record_data;
  RC rc = make_record(value_num, values, record_data);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  Record record;
  record.set_data(record_data);
  rc = insert_record(trx, &record);
  delete[] record_data;
  return rc;
}


RC Table::insert_text_data(const char *data) {
  PageNum page_num;
  RC rc = RC::SUCCESS;
  
  // 1. 对于text类型的字段，调用record_manager申请的新page，将values中的数据拷贝出来拷贝到新page中
  if ((rc = record_handler_->insert_text_data(page_num, data)) != RC::SUCCESS) {
    LOG_ERROR("Failed to insert text data.");
    return rc;
  }
  // 2. 修改values中的数据，存储的数据为页号
  memcpy((void *)data, &page_num, sizeof(int32_t));

  return rc;
}

RC Table::delete_text(Record *record, FieldMeta &field_meta) {
  // 1. 根据record和field_meta获取页号
  PageNum page_num; 
  memcpy(&page_num, record->data() + field_meta.offset(), sizeof(int32_t));
  // 2. 调用record_manager清空该页
  RC rc = record_handler_->delete_text_data(page_num);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete text data.");
    return rc;
  }
  return rc;
}


RC Table::update_text(Record *record, const FieldMeta *field_meta, const char *data) {
  // 1. 根据record和field_meta获取页号
  PageNum page_num; 
  memcpy(&page_num, record->data() + field_meta->offset(), sizeof(int32_t));
  RC rc = record_handler_->update_text_data(page_num, data);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to update text data.");
    return rc; 
  }
  return rc;
}


RC Table::get_text_data(Record *record, const FieldMeta *field_meta, char *data) const {
  PageNum page_num; 
  memcpy(&page_num, record->data() + field_meta->offset(), sizeof(int32_t));
  RC rc = record_handler_->get_text_data(page_num, data);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get text data.");
    return rc;
  }
  return rc;
}

RC Table::get_text_data(const Record &record, int offset, char *data) const {
  PageNum page_num; 
  memcpy(&page_num, record.data() + offset, sizeof(int32_t));
  RC rc = record_handler_->get_text_data(page_num, data);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get text data.");
    return rc;
  }
  return rc;
}

const char *Table::name() const
{
  return table_meta_.name();
}

const TableMeta &Table::table_meta() const
{
  return table_meta_;
}

RC Table::make_record(int value_num, const Value *values, char *&record_out)
{
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }
  int bitmap = 0;
  const int normal_field_start_index = table_meta_.sys_field_num();
  for (size_t i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];
    int index = field->index();
    if (value.type == AttrType::NULL_) {
      bitmap |= (1 << index);
      continue;
    } else {
      bitmap &= ~(1 << index); 
    }
    if (field->type() != value.type) {
      LOG_ERROR("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
          table_meta_.name(),
          field->name(),
          field->type(),
          value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }


  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record = new char[record_size];

  // 复制bitmap
  memcpy(record + table_meta_.bitmap_offset(), &bitmap, BASE_BITMAP_SIZE);

  RC rc = RC::SUCCESS;
  for (size_t i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];
    size_t copy_len = field->len();
    if (value.type == NULL_) {
      continue;
    } else if (field->type() == CHARS) {
      const size_t data_len = strlen((const char *)value.data);
      // 如果data_len > copy_len 防止超过record_size大小导致内存越界
      if (copy_len > data_len) {
        copy_len = data_len + 1;
      }
    } else if (field->type() == TEXTS) {
      if ((rc = insert_text_data((const char *)value.data)) != RC::SUCCESS) {
        return rc;
      }
      // TODO(vanish): 默认field->len()为4，其实可以不用做额外处理？
      // 字节类型长度默认也是4个字节，所以可以不同担心越界问题
      copy_len = sizeof(PageNum);
    }
    memcpy(record + field->offset(), value.data, copy_len);
  }
  record_out = record;
  return rc;
}

RC Table::init_record_handler(const char *base_dir)
{
  std::string data_file = table_data_file(base_dir, table_meta_.name());

  
  // 判断text_data_file文件是否存在
  RC rc = BufferPoolManager::instance().open_file(data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  std::fstream fs;
  std::string text_data_file = table_text_file(base_dir, table_meta_.name());
  fs.open(text_data_file, std::ios_base::in | std::ios_base::binary);
  if (fs.is_open()) {
    fs.close();
    RC rc = BufferPoolManager::instance().open_file(text_data_file.c_str(), text_buffer_pool_);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", text_data_file.c_str(), rc, strrc(rc));
      return rc;
    }
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(data_buffer_pool_, text_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner)
{
  RC rc = scanner.open_scan(*data_buffer_pool_, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%d:%s", rc, strrc(rc));
  }
  return rc;
}

RC Table::check_unique(Value *values, int value_num) {
  char *record_data;
  RC rc = RC::SUCCESS;
  // value_num < table field_num 表示这是更新操作
  if (value_num < table_meta_.field_num() - table_meta_.sys_field_num()) {
    record_data = nullptr;
    return RC::GENERIC_ERROR;
  } else {
    rc = make_record(value_num, values, record_data);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
  }

  // TODO(vanish): 完善multi-index后，完全可以通过索引来快速定位重复值
  for (auto index: indexes_) {
    const IndexMeta index_meta = index->index_meta();
    auto fields = index_meta.fields();

    if (index_meta.unique()) {
      RecordFileScanner scanner;
      rc = scanner.open_scan(*data_buffer_pool_, nullptr);
        if (rc != RC::SUCCESS) {
        LOG_ERROR("failed to open scanner. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      Record record;
      while (scanner.has_next()) {
        rc = scanner.next(record);
        int bitmap = *(int *)(record.data() + table_meta_.bitmap_offset());
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to fetch next record. rc=%d:%s", rc, strrc(rc));
          return rc;
        }
        bool flag = true;
        // 遍历各个字段，判断对应字段是否存在对应值
        // 因为插入时所有字段的数据都有
        for (auto field: fields) {
          const FieldMeta *field_meta = table_meta_.field(field.c_str());
          size_t offset = field_meta->offset();
          size_t len = field_meta->len();
          // 这里如果某个字段为NULL直接可以插入
          bool is_null = 1 & (bitmap >> field_meta->index());
          // 是否需要考虑不同类型之间内存对齐问题？
          if (record_data != nullptr) {
            if (0 != memcmp(record.data() + offset, record_data + offset, len) || is_null) {
              flag = false;
              break;
            }
          }
        }
        // flag==true 表明有和索引中所有字段都重复的record，返回error
        if (flag == true) {
          LOG_ERROR("failed to insert\\update, because of duplicate values. rc=%d:%s", rc, strrc(rc));
          return RC::GENERIC_ERROR;
        }
      }
    }
  }
  return rc;
}


RC Table::check_unique(std::vector<const FieldMeta *> field_metas, std::vector<const Value *> values, const Condition conditions[], int condition_num) {

  // 满足条件的行会被update
  // 找到可能会被修改的行
  CompositeConditionFilter condition_filter;
  RC rc = condition_filter.init(*this, conditions, condition_num);
  int record_size = table_meta_.record_size();

  
  for (auto index: indexes_) {
    const IndexMeta index_meta = index->index_meta();
    auto fields = index_meta.fields();

    if (index_meta.unique()) {
      RecordFileScanner scanner;
      std::unordered_set<std::string> unique_set;
      rc = scanner.open_scan(*data_buffer_pool_, &condition_filter);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("failed to open scanner. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      Record record;
      while (scanner.has_next()) {
        rc = scanner.next(record);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to fetch next record. rc=%d:%s", rc, strrc(rc));
          return rc;
        }
        // 不能直接使用record.data()，需要拷贝一下
        char update_data[record_size];
        memcpy(update_data, record.data(), record_size);
        // 将临时record更新为更新后的值
        for (size_t i=0; i<values.size(); i++) {
          if (values[i]->type == AttrType::NULL_) {
            continue;
          }
          char *copy_to = update_data + field_metas[i]->offset();
          if (field_metas[i]->type() == AttrType::CHARS) {
            memcpy(copy_to, values[i]->data, std::min(field_metas[i]->len(), (int)strlen((char *) values[i]->data))+1);
          } else {
            memcpy(copy_to, values[i]->data, field_metas[i]->len());
          }
        }

        char data[record_size];
        size_t length = 0;
        // 遍历各个字段，判断对应字段是否存在对应值
        for (auto field: fields) {
          const FieldMeta *field_meta = table_meta_.field(field.c_str());
          size_t offset = field_meta->offset();
          size_t len = field_meta->len();
          memcpy(data + length, update_data + offset, len);
          length += len;
        }
        std::string str;
        str.assign(data, length);
        if (unique_set.find(str) != unique_set.end()) {
          LOG_ERROR("failed to update, because of duplicate values. rc=%d:%s", rc, strrc(rc));
          return RC::GENERIC_ERROR;
        }
        unique_set.insert(str);
      }

      scanner.close_scan();

      rc = scanner.open_scan(*data_buffer_pool_, nullptr);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to fetch next record. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
      while (scanner.has_next()) {
        rc = scanner.next(record);
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to fetch next record. rc=%d:%s", rc, strrc(rc));
          return rc;
        }
        int bitmap = *(int *)(record.data() + table_meta_.bitmap_offset());

        char data[record_size];
        size_t length = 0;
        // 遍历各个字段，判断对应字段是否存在对应值
        bool has_null = false;
        for (auto field: fields) {
          const FieldMeta *field_meta = table_meta_.field(field.c_str());
          // 判断该字段是否对应值是否为null
          if (1 & (bitmap >> field_meta->index())) {
            has_null = true;
            break;
          }
          size_t offset = field_meta->offset();
          size_t len = field_meta->len();
          memcpy(data + length, record.data() + offset, len);
          length += len;
        }
        // 有字段为null，继续continue
        if (has_null) {
          continue;
        }
        std::string str;
        str.assign(data, length);
        if (unique_set.find(str) != unique_set.end()) {
          LOG_ERROR("failed to update, because of duplicate values. rc=%d:%s", rc, strrc(rc));
          return RC::GENERIC_ERROR;
        }
        unique_set.insert(str);
      }
    }
  }
  return RC::SUCCESS;
}

RC Table::check_unique_before_create(const char *attribute_name[], size_t attr_num) {

  RecordFileScanner scanner;
  RC rc = scanner.open_scan(*data_buffer_pool_, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  std::unordered_set<std::string> check_set;
  Record record;
  while (scanner.has_next()) {
    rc = scanner.next(record);
    std::string s;

    int bitmap = *(int *)(record.data() + table_meta_.bitmap_offset());
    bool has_null = false;
    for (size_t i = 0; i < attr_num; i++) {

      const FieldMeta *field_meta = table_meta_.field(attribute_name[i]);
      if (1 & (bitmap >> field_meta->index())) {
        has_null = true;
        break;
      }
      int offset = field_meta->offset();
      s.append(record.data()+offset, field_meta->len());
    }

    // 如果有重复值，并且字段中没有null值
    if (check_set.find(s) != check_set.end() && !has_null) {
      LOG_ERROR("failed to create unique index, because of duplicate values. rc=%d:%s", rc, strrc(rc));
      return RC::GENERIC_ERROR;
    }

    check_set.insert(s);
  }
  return RC::SUCCESS;
}


/**
 * 为了不把Record暴露出去，封装一下
 */
class RecordReaderScanAdapter {
public:
  explicit RecordReaderScanAdapter(void (*record_reader)(const char *data, void *context), void *context)
      : record_reader_(record_reader), context_(context)
  {}

  void consume(const Record *record)
  {
    record_reader_(record->data(), context_);
  }

private:
  void (*record_reader_)(const char *, void *);
  void *context_;
};

static RC scan_record_reader_adapter(Record *record, void *context)
{
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter,
		      int limit, void *context,
		      void (*record_reader)(const char *data, void *context))
{
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter, scan_record_reader_adapter);
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context,
                      RC (*record_reader)(Record *record, void *context))
{
  if (nullptr == record_reader) {
    return RC::INVALID_ARGUMENT;
  }

  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  IndexScanner *index_scanner = find_index_for_scan(filter);
  if (index_scanner != nullptr) {
    return scan_record_by_index(trx, index_scanner, filter, limit, context, record_reader);
  }

  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  rc = scanner.open_scan(*data_buffer_pool_, filter);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  int record_count = 0;
  Record record;
  while (scanner.has_next()) {
    rc = scanner.next(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to fetch next record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
    if (trx == nullptr || trx->is_visible(this, &record)) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        break;
      }
      record_count++;
    }
  }

  scanner.close_scan();
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter,
                               int limit, void *context,
                               RC (*record_reader)(Record *, void *))
{
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);
    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
      break;
    }

    if ((trx == nullptr || trx->is_visible(this, &record)) && (filter == nullptr || filter->filter(record))) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
public:
  explicit IndexInserter(Index *index) : index_(index)
  {}

  RC insert_index(const Record *record)
  {
    return index_->insert_entry(record->data(), &record->rid());
  }

private:
  Index *index_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context)
{
  IndexInserter &inserter = *(IndexInserter *)context;
  return inserter.insert_index(record);
}

// TODO(vanish): Multi-index 修改arribute_name为数组
RC Table::create_index(Trx *trx, const char *index_name, const char *attribute_name[], size_t attr_num, int is_unique)
{
  if (common::is_blank(index_name)) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }
  if (table_meta_.index(index_name) != nullptr) {
    LOG_INFO("Invalid input arguments, table name is %s, index %s exist",
          name(), index_name);
  }
  for (size_t i = 0; i < attr_num; i++) {
    if (common::is_blank(attribute_name[i])) {
        LOG_INFO("Invalid input arguments, table name is %s, index_name is blank", name());
        return RC::INVALID_ARGUMENT;
    }
  }

  if (table_meta_.index(index_name) != nullptr || table_meta_.find_index_by_field(attribute_name, attr_num)) {
    LOG_INFO("Invalid input arguments, table name is %s, index %s exist or attribute %s exist index",
             name(), index_name, attribute_name[0]);
    return RC::SCHEMA_INDEX_EXIST;
  }

  std::vector<std::string> fields;
  std::vector<const FieldMeta *>  field_metas;
  for (size_t i=0; i<attr_num; i++) {
    const FieldMeta *field_meta = table_meta_.field(attribute_name[i]);
    if (!field_meta) {
      LOG_INFO("Invalid input arguments, there is no field of %s in table:%s.", attribute_name[i], name());
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.emplace_back(field_meta->name());
    field_metas.emplace_back(field_meta);
  }

  // 检查字段是否为unique
  if (is_unique && RC::SUCCESS != check_unique_before_create(attribute_name, attr_num)) {
    return RC::GENERIC_ERROR;
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, std::move(fields), is_unique);
  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s, field_name:%s",
             name(), index_name, attribute_name);
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = table_index_file(base_dir_.c_str(), name(), index_name);

  // TODO(Vanish): multi-index 修改create语句，
  rc = index->create(index_file.c_str(), new_index_meta, *field_metas[0]);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
        tmp_file.c_str(),
        meta_file.c_str(),
        index_name,
        name(),
        errno,
        strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());

  return rc;
}

RC Table::show_index(std::ostream &os) {
  for (size_t i=0; i < IDNEX_HEADER_NUM; i++) {
    if (i != 0) {
      os << " | ";
    }
    os << INDEX_HEADER[i];
  }
  os << '\n';
  for (Index *index: indexes_) {
    const IndexMeta index_meta = index->index_meta();
    auto fields = index_meta.fields();
    bool non_unique = !index_meta.unique();
    for (size_t i=0; i<fields.size(); i++) {
      os << name() << " | " << non_unique << " | " << index_meta.name() << " | " <<  i+1 << " | " << fields[i] << "\n";
    }
  }
  return RC::SUCCESS;
}

class RecordUpdater {
  public:
    RecordUpdater(Trx *trx, Table *table, const FieldMeta *field_meta, const Value *value) : trx_(trx), table_(table), field_meta_(field_meta), value_(value) {}
    RC update_record(Record *record) {
      RC rc = table_->update_record(trx_, record, field_meta_, value_);
      if (RC::SUCCESS == rc) {
        ++updated_count_;
      }
      return rc;
    }

    int updated_count() const {
      return updated_count_;
    }
  
  private:
    Trx *trx_;
    Table *table_;
    const FieldMeta *field_meta_;
    const Value *value_;
    int updated_count_ = 0;
};

static RC record_update_adapter(Record *record, void *context)
{
  RecordUpdater &record_updater = *(RecordUpdater *)context;
  return record_updater.update_record(record);
}

RC Table::update_record(Trx *trx, Record *record, const FieldMeta *field_meta, const Value *value) {
  RC rc = delete_entry_of_indexes(record->data(), record->rid(), false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
              record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
  }
  if (field_meta->type() == AttrType::TEXTS) {
    rc = update_text(record, field_meta, (const char *)value->data);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  char *copy_to = record->data() + field_meta->offset();
  // 1. 修改record中的数据
  // 如果是TEXT类型，不需要修改record数据
  if (field_meta->type() == AttrType::CHARS) {
    memcpy(copy_to, value->data, std::min(field_meta->len(), (int)strlen((char *) value->data))+1);
  } else if (field_meta->type() != AttrType::TEXTS) {
      memcpy(copy_to, value->data, field_meta->len());
  }

  rc = record_handler_->update_record(record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to update record of record (rid=%d.%d). rc=%d:%s", 
              record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
    return rc;
  }
  rc = insert_entry_of_indexes(record->data(), record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to insert indexes of record (rid=%d.%d). rc=%d:%s",
              record->rid().page_num, record->rid().slot_num, rc, strrc(rc));

    return rc;
  }
  // 2. 将record写回page中
  return rc;
}


RC Table::commit_update(Trx *trx, const RID &rid) {
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get record %s: %s", this->name(), rid.to_string().c_str());
    return rc;
  }
  return trx->commit_update(this, record);
}


RC Table::rollback_update(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  return rc;
}

// TODO(vanish): update-select 将const FieldMeta *field_meta改为多个字段值,  const Value *value同理
RC Table::update_record(Trx *trx, Record *record, std::vector<const FieldMeta *> field_metas, std::vector<const Value *> values) {
  RC rc = delete_entry_of_indexes(record->data(), record->rid(), false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
              record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
  }
  
  int bitmap = *(int *)(record->data() + table_meta_.bitmap_offset());
  // 1. 修改record中的数据
  // 如果是TEXT类型，不需要修改record数据
  for (size_t i=0; i<values.size(); i++) {
    // 更新bitmap
    int index = field_metas[i]->index();
    if (values[i]->type == AttrType::NULL_) {
      bitmap |= (1 << index);
      continue;
    } else {
      bitmap &= ~(1 << index); 
    }

    if (field_metas[i]->type() == AttrType::TEXTS) {
      rc = update_text(record, field_metas[i], (const char *)values[i]->data);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
    char *copy_to = record->data() + field_metas[i]->offset();
    if (field_metas[i]->type() == AttrType::CHARS) {
      memcpy(copy_to, values[i]->data, std::min(field_metas[i]->len(), (int)strlen((char *) values[i]->data))+1);
    } else if (field_metas[i]->type() != AttrType::TEXTS) {
      memcpy(copy_to, values[i]->data, field_metas[i]->len());
    }
  }
  memcpy(record->data() + table_meta_.bitmap_offset(), &bitmap, BASE_BITMAP_SIZE);

  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }


  rc = record_handler_->update_record(record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to update record of record (rid=%d.%d). rc=%d:%s", 
              record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
  }
  rc = insert_entry_of_indexes(record->data(), record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to insert indexes of record (rid=%d.%d). rc=%d:%s",
              record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
  }

  if (trx != nullptr) {
    rc = trx->update_record(this, record);

    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(update) to trx");
      RC rc2 = record_handler_->delete_record(&record->rid());
      if (rc2 != RC::SUCCESS) {
        LOG_ERROR("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
            name(),
            rc2,
            strrc(rc2));
      }
      return rc;
    }
    CLogRecord *clog_record = nullptr;
    rc = clog_manager_->clog_gen_record(CLogType::REDO_UPDATE, trx->get_current_id(), clog_record, name(), table_meta_.record_size(), record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a clog record. rc=%d:%s", rc, strrc(rc));
      return rc;      
    }
    rc = clog_manager_->clog_append_record(clog_record);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  // 2. 将record写回page中
  return rc;
}

RC Table::update_record(Trx *trx, const char *attribute_name, const Value *value, int condition_num,
    const Condition conditions[], int *updated_count)
{

  // 1. 根据条件创建过滤器
  CompositeConditionFilter condition_filter;
  RC rc = condition_filter.init(*this, conditions, condition_num);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create CompositeConditionFilter!");
    return rc;
  }

  // 2. 创建RecordUpdater
  // 2.1 获取field_meta
  const FieldMeta *field_meta = table_meta().field(attribute_name);
  if (nullptr == field_meta) {
    LOG_ERROR("Invalid value attribute_name: %s", attribute_name);
    return RC::SCHEMA_FIELD_MISSING;
  }


  // 2.2 创建RecordUpdater
  RecordUpdater updater = RecordUpdater(trx, this, field_meta, value);

  // 3. 调用scan_record
  rc = scan_record(trx, &condition_filter, -1, &updater, record_update_adapter);
  if (updated_count != nullptr) {
    *updated_count = updater.updated_count();
  }
  return RC::GENERIC_ERROR;
}

class RecordDeleter {
public:
  RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx)
  {}

  RC delete_record(Record *record)
  {
    RC rc = RC::SUCCESS;
    rc = table_.delete_record(trx_, record);
    if (rc == RC::SUCCESS) {
      deleted_count_++;
    }
    return rc;
  }

  int deleted_count() const
  {
    return deleted_count_;
  }

private:
  Table &table_;
  Trx *trx_;
  int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context)
{
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count)
{
  RecordDeleter deleter(*this, trx);
  RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::delete_record(Trx *trx, Record *record)
{
  RC rc = RC::SUCCESS;
  
  rc = delete_entry_of_indexes(record->data(), record->rid(), false);  // 重复代码 refer to commit_delete
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
                record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
    return rc;
  } 
  
  // 在这里调用delete_text
  const std::vector<FieldMeta> *field_metas = table_meta().field_metas();
  for (auto field: *field_metas) {
    if (field.type() == TEXTS) {
      if (RC::SUCCESS != delete_text(record, field)) {
        LOG_ERROR("Failed to delete text data. field_name = %s", field.name());
        return RC::GENERIC_ERROR;
      }
    }
  }

  rc = record_handler_->delete_record(&record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete record (rid=%d.%d). rc=%d:%s",
                record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->delete_record(this, record);
    
    CLogRecord *clog_record = nullptr;
    rc = clog_manager_->clog_gen_record(CLogType::REDO_DELETE, trx->get_current_id(), clog_record, name(), 0, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a clog record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
    rc = clog_manager_->clog_append_record(clog_record);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return rc;
}

RC Table::recover_delete_record(Record *record)
{
  RC rc = RC::SUCCESS;
  rc = record_handler_->delete_record(&record->rid());
  
  return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid)
{
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = delete_entry_of_indexes(record.data(), record.rid(), false);

  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
        rid.page_num, rid.slot_num, rc, strrc(rc));  // panic?
  }

  rc = record_handler_->delete_record(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid)
{
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->rollback_delete(this, record);  // update record in place
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(const char *field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

IndexScanner *Table::find_index_for_scan(const DefaultConditionFilter &filter)
{
  const ConDesc *field_cond_desc = nullptr;
  const ConDesc *value_cond_desc = nullptr;
  if (filter.left().is_attr && !filter.right().is_attr) {
    field_cond_desc = &filter.left();
    value_cond_desc = &filter.right();
  } else if (filter.right().is_attr && !filter.left().is_attr) {
    field_cond_desc = &filter.right();
    value_cond_desc = &filter.left();
  }
  if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
    return nullptr;
  }

  const FieldMeta *field_meta = table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
  if (nullptr == field_meta) {
    LOG_PANIC("Cannot find field by offset %d. table=%s", field_cond_desc->attr_offset, name());
    return nullptr;
  }

  const IndexMeta *index_meta = table_meta_.find_index_by_field(field_meta->name());
  if (nullptr == index_meta) {
    return nullptr;
  }

  Index *index = find_index(index_meta->name());
  if (nullptr == index) {
    return nullptr;
  }

  const char *left_key = nullptr;
  const char *right_key = nullptr;
  int left_len = 4;
  int right_len = 4;
  bool left_inclusive = false;
  bool right_inclusive = false;
  switch (filter.comp_op()) {
  case EQUAL_TO: {
    left_key = (const char *)value_cond_desc->value;
    right_key = (const char *)value_cond_desc->value;
    left_inclusive = true;
    right_inclusive = true;
  }
    break;
  case LESS_EQUAL: {
    right_key = (const char *)value_cond_desc->value;
    right_inclusive = true;
  }
    break;
  case GREAT_EQUAL: {
    left_key = (const char *)value_cond_desc->value;
    left_inclusive = true;
  }
    break;
  case LESS_THAN: {
    right_key = (const char *)value_cond_desc->value;
    right_inclusive = false;
  }
    break;
  case GREAT_THAN: {
    left_key = (const char *)value_cond_desc->value;
    left_inclusive = false;
  }
    break;
  default: {
    return nullptr;
  }
  }

  if (filter.attr_type() == CHARS) {
    left_len = left_key != nullptr ? strlen(left_key) : 0;
    right_len = right_key != nullptr ? strlen(right_key) : 0;
  }
  return index->create_scanner(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
}

IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter)
{
  if (nullptr == filter) {
    return nullptr;
  }

  // remove dynamic_cast
  const DefaultConditionFilter *default_condition_filter = dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    return find_index_for_scan(*default_condition_filter);
  }

  const CompositeConditionFilter *composite_condition_filter = dynamic_cast<const CompositeConditionFilter *>(filter);
  if (composite_condition_filter != nullptr) {
    int filter_num = composite_condition_filter->filter_num();
    for (size_t i = 0; i < filter_num; i++) {
      IndexScanner *scanner = find_index_for_scan(&composite_condition_filter->filter(i));
      if (scanner != nullptr) {
        return scanner;  // 可以找到一个最优的，比如比较符号是=
      }
    }
  }
  return nullptr;
}

RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
