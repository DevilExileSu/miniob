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
// Created by wangyunlai on 2022/9/28
//

#pragma once

#include <string>

#include "rc.h"
#include "sql/expr/tuple_cell.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/field_meta.h"


std::string double2string(double v);

std::string int2string(int v);

std::string float2string(float v);

int string2int(char *v);

float string2float(char *v);

int check_prefix(char *v);

bool like_match(const char *a, const char *b);

RC convert(const FieldMeta *field_meta, Value *value, bool &has_text);

RC convert(AttrType type, Value *value, bool &has_text);

void value_init_from_cell(TupleCell cell, Value *value);