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

#include "sql/stmt/insert_stmt.h"
#include "sql/parser/parse_defs.h"
#include "common/log/log.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "util/util.h"
#include <cmath>

InsertStmt::InsertStmt(Table *table, std::vector<const Value *> &&values, std::vector<int> &&value_amount)
    : table_(table), values_(values), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db, const Inserts &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name;
  if (nullptr == db || nullptr == table_name || inserts.insert_num <= 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d", db, table_name, inserts.insert_num);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();
  const int sys_field_num = table_meta.sys_field_num();

  std::vector<const FieldMeta *> field_list;
  for (int i = 0; i < field_num; i++) {
    field_list.emplace_back(table_meta.field(i + sys_field_num));
  }

  std::vector<const Value *> values_list;
  std::vector<int> value_amount_list;

  for (int i = 0; i < inserts.insert_num; i++) {
    Insert *insert = const_cast<Insert *>(&inserts.inserts[i]);
    Value *values = insert->values;
    int value_num = insert->value_num;

    // check the fields number
    if (field_num != value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }

    bool has_text = false;
    // check fields type
    for (int i = 0; i < value_num; i++) {
      // 字段可以为null值，并且values[i].type类型为NULL_
      // 跳过不进行后面的convert
      if (field_list[i]->nullable() && AttrType::NULL_ == values[i].type) {
        continue;
      }
      RC rc = convert(field_list[i], &values[i], has_text);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
    
    values_list.emplace_back(values);
    value_amount_list.emplace_back(value_num);

    // unique-index: 检查是否满足unique，如果存在text类型直接跳过
    // TODO(Vanish): 引入NULL类型后，unique校验，也会收到影响，但是实际测试并没有索引列为nullable的情况
    RC rc = RC::SUCCESS;
    if (!has_text) {
      if ((rc = table->check_unique(values, value_num)) != RC::SUCCESS) {
        return rc; 
      }
    }
  }

  // everything alright
  stmt = new InsertStmt(table, std::move(values_list), std::move(value_amount_list));
  return RC::SUCCESS;
}
