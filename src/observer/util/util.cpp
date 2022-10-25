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

#include <string.h>
#include <cmath>

#include "rc.h"
#include "util/util.h"
#include "common/log/log.h"

std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
      
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return std::string(buf, len);
}


std::string int2string(int v) {
  return std::to_string(v);
}

std::string float2string(float v) {
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
  }
  if (buf[len - 1] == '.') {
    len--;
  }
  return std::string(buf, len);
}


int float2int(float v) {
  return static_cast<int>(v + 0.5);
}

float int2float(int v) {
 return static_cast<float>(v); 
}

int string2int(std::string v) {
  return atoi(v.c_str());
}

float string2float(std::string v) {
  return atof(v.c_str());
}

int check_prefix(std::string v) {
  int res = 1;
  int dot_cnt = 0;
  for (size_t i = 0; i < v.size(); i++) {
    if (v[i] >= '0' && v[i] <= '9') {
      continue;
    } else if (v[i] == '.' && i > 0 && dot_cnt == 0) {
        ++dot_cnt;
      res = 2;
    } else if (i > 0) {
      if (v[i-1] == '.') {
        res = 1;
        v = v.substr(0, i-1);
      } else {
        v = v.substr(0, i);
      }
      return res;
    } else {
      res = 0;
      break;
    } 
  }
  return res;
}
 

 // TODO 改成贪心，leetcode 44
 bool like_match(const char *a, const char *b) {
  int m = strlen(a);
  int n = strlen(b);
  int dp[m+1][n+1];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = true;
  for (int i=1; i<=n; ++i) {
    if (b[i-1] == '%') {
      dp[0][i] = true;
    } else {
      break;
    }
  }

  for (int i=1; i<=m; ++i) {
    for (int j=1; j<=n; ++j) {
      if (b[j-1] == '%') {
        dp[i][j] = dp[i][j-1] | dp[i-1][j];
      } else if (b[j-1] == '_' || a[i-1] == b[j-1]) {
        dp[i][j] = dp[i-1][j-1];
      }
    }
  }
  return dp[m][n];
 }


 RC convert(const FieldMeta *field_meta, Value *value, bool &has_text) {
    const AttrType value_type = value->type;
    if (field_meta->type() != value_type) {
      switch (field_meta->type()) {
        case INTS:
          switch (value_type) {
            case FLOATS: {
              int n = round(*(float *)value->data);
              value_destroy(value);
              value_init_integer(value, n);
              value->type = INTS;
              break;
            }
            case CHARS: {
              int n = round(atof((char *)value->data));
              value_destroy(value);
              value_init_integer(value, n);
              break;
            }
            default:
              LOG_WARN("schema mismatch. value type=%d, field type in schema=%d", value_type, field_meta->type());
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          break;
        case FLOATS:
          switch (value_type) {
            case INTS: {
              float f = *(int *)value->data;
              value_destroy(value);
              value_init_float(value, f);
              break;
            }
            case CHARS: {
              float f = atof((char *)value->data);
              value_destroy(value);
              value_init_float(value, f);
              break;
            }
            default:
              LOG_WARN("schema mismatch. value type=%d, field type in schema=%d", value_type, field_meta->type());
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          break;
        case CHARS:
          switch (value_type) {
            case INTS: {
              std::string s = int2string(*(int *)value->data);
              value_destroy(value);
              value_init_string(value, s.c_str());
              break;
            }
            case FLOATS: {
              std::string s = float2string(*(float *)value->data);
              value_destroy(value);
              value_init_string(value, s.c_str());
              break;
            }
            default:
              LOG_WARN("schema mismatch. value type=%d, field type in schema=%d", value_type, field_meta->type());
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          break;
        case TEXTS:
          // value_type 不可能是TEXTS类型，所以这里不需要考虑把TEXTS类型转换为其他类型
          has_text = true;
          switch (value_type) {
            case INTS: {
              std::string s = int2string(*(int *)value->data);
              value_destroy(value);
              value_init_string(value, s.c_str());
              value->type = TEXTS;
              break;
            }
            case FLOATS: {
              std::string s = float2string(*(float *)value->data);
              value_destroy(value);
              value_init_string(value, s.c_str());
              value->type = TEXTS;
              break;
            }
            case CHARS: {
              value->type = TEXTS;
              break;
            }
            default:
              LOG_WARN("schema mismatch. value type=%d, field type in schema=%d", value_type, field_meta->type());
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
          break;
        
        default:
          LOG_WARN("schema mismatch. value type=%d, field type in schema=%d", value_type, field_meta->type());
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
    return RC::SUCCESS;
 }