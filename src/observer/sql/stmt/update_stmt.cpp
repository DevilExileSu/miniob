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
// Created by Wangyunlai on 2022/5/22.
//

#include "common/log/log.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field_meta.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

UpdateStmt::UpdateStmt(Table *table, FilterStmt *filter_stmt, const Value *values, int value_amount, const FieldMeta *field_meta)
  : table_(table), filter_stmt_(filter_stmt), values_(values), value_amount_(value_amount), field_meta_(field_meta)
{}

UpdateStmt::~UpdateStmt() {
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}


RC UpdateStmt::create(Db *db, const Updates &update, Stmt *&stmt)
{
  // TODO
  const char *table_name = update.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db = %p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  // 2. 检查表中是否存在属性
  const TableMeta &table_meta = table->table_meta();
  const FieldMeta *field_meta = table_meta.field(update.attribute_name);
  if (nullptr == field_meta) {
    LOG_WARN("Invalid value attribute_name: %s", update.attribute_name);
    return RC::SCHEMA_FIELD_MISSING;
  }
  // 3. 检查Value类型是否和表属性类型一致
  const Value *value = &update.value;
  if (value == nullptr) {
    LOG_WARN("parse error");
    return RC::GENERIC_ERROR;
  }
  if (field_meta->type() != value->type) {
      LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d", 
               table_name, field_meta->name(), field_meta->type(), value->type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  // 构建 filterstmt 用于传递给 predict operator， 谓词算子
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update.conditions, update.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  int value_amount = 1;

  stmt = new UpdateStmt(table, filter_stmt, value, value_amount, field_meta);
  return rc;
}
