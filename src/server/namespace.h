/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#pragma once

#include "storage/storage.h"

constexpr const char *kNamespaceDBKey = "__namespace_keys__";

class Namespace {
 public:
  explicit Namespace(engine::Storage *storage)
      : storage_(storage), cf_(storage_->GetCFHandle(ColumnFamilyID::Propagate)) {}

  ~Namespace() = default;
  Namespace(const Namespace &) = delete;
  Namespace &operator=(const Namespace &) = delete;

  Status LoadAndRewrite();
  StatusOr<std::string> Get(const std::string &ns) const;
  StatusOr<std::string> GetByToken(const std::string &token) const;
  Status Set(const std::string &ns, const std::string &token);
  Status Add(const std::string &ns, const std::string &token);
  Status Del(const std::string &ns);
  const std::map<std::string, std::string> &List() const { return tokens_; }
  Status Rewrite();
  bool IsAllowModify() const;

 private:
  engine::Storage *storage_;
  rocksdb::ColumnFamilyHandle *cf_ = nullptr;
  std::map<std::string, std::string> tokens_;
};
