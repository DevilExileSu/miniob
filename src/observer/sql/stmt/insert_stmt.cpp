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
#include "common/log/log.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

InsertStmt::InsertStmt(Table *table, std::vector<const Value *> &&values, std::vector<int> &&value_amount)
  : table_ (table), values_(values), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db, const Inserts &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name;
  if (nullptr == db || nullptr == table_name || inserts.insert_num <= 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d", 
             db, table_name, inserts.insert_num);
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
  for (int i=0; i < field_num; i++) {
    field_list.emplace_back(table_meta.field(i + sys_field_num));
  }

  std::vector<const Value *> values_list;
  std::vector<int> value_amount_list;

  for (int i = 0; i < inserts.insert_num; i++) {
    // const Insert insert = inserts.inserts[i];
    // const Value *values = insert.values;
    int value_num = inserts.inserts[i].value_num;
    // check the fields number
    if (field_num != value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // check fields type
    for (int j = 0;  j < value_num; j++) {
      const AttrType value_type = inserts.inserts[i].values[j].type;
      if (field_list[j]->type() != value_type) { // TODO try to convert the value type to field type
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d", 
                table_name, field_list[j]->name(), field_list[j]->type(), value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
    values_list.emplace_back(&inserts.inserts[i].values[0]);
    // values_list.emplace_back(&insert.values[0]);
    value_amount_list.emplace_back(value_num);
  }

  // everything alright
  stmt = new InsertStmt(table, std::move(values_list), std::move(value_amount_list));
  return RC::SUCCESS;
}
