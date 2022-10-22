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
// Created by Meiyi & Wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString FIELD_UNIQUE("is_unique");


RC IndexMeta::init(const char *name, std::vector<std::string> &&fields, int is_unique)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  fields_ = fields;
  unique_ = (is_unique == 1);
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  Json::Value fields_name;
  for (auto &field : fields_) {
    fields_name.append(Json::Value(field));
  }
  json_value[FIELD_UNIQUE] = Json::Value(unique_);
  json_value[FIELD_FIELD_NAME] = std::move(fields_name);
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique_value = json_value[FIELD_UNIQUE];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }
  if (!unique_value.isBool()) {
    return RC::GENERIC_ERROR;
  }
  if (!field_value.empty()) { 
    if (!field_value.isArray()) {
      LOG_ERROR("Field name of index [%s] is not a array.",
          name_value.asCString());
      return RC::GENERIC_ERROR;
    }
  }

  std::vector<std::string> fields;
  for (int i=0; i<field_value.size(); i++) {
    if (!field_value[i].isString()) {
      LOG_ERROR("Field name of index [%s] is not a array. json value=%s", 
                name_value.asCString(), field_value[i].toStyledString().c_str());
      return RC::GENERIC_ERROR;
    }
    fields.emplace_back(std::string(field_value[i].asCString()));
  }

  for (auto &field: fields) {
    const FieldMeta *field_meta =table.field(field.c_str());
    if (nullptr == field_meta) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  return index.init(name_value.asCString(), std::move(fields), unique_value.asBool());
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

std::vector<std::string> IndexMeta::fields() const {
  return fields_;
}

const char *IndexMeta::field() const
{
  return fields_[0].c_str();
}

bool IndexMeta::unique() const {
  return unique_;
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", field=" << fields_[0];
}