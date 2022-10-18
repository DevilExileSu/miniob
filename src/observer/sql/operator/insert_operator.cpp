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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/insert_operator.h"
#include "sql/stmt/insert_stmt.h"
#include "storage/common/table.h"
#include "rc.h"

RC InsertOperator::open()
{
  Table *table = insert_stmt_->table();
  std::vector<const Value *> values = insert_stmt_->values();
  std::vector<int> value_amount = insert_stmt_->value_amount();
  RC rc = RC::SUCCESS;
  for (size_t i=0; i<values.size(); i++) {
    rc = table->insert_record(nullptr, value_amount[i], values[i]);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  return rc; // TODO trx
}

RC InsertOperator::next()
{
  return RC::RECORD_EOF;
}

RC InsertOperator::close()
{
  return RC::SUCCESS;
}
