/* Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once
#include <google/protobuf/text_format.h>

#include <functional>

#include "paddle/fluid/framework/program_desc.h"
namespace paddle {
namespace framework {

void MergePrograms(ProgramDesc *dst,
                   const std::vector<ProgramDesc> &srcs,
                   bool append);

class ProgramProcessor {
 public:
  ProgramProcessor();

  void GetInputsOutputsInBlock(const BlockDesc &current_block,
                               std::set<std::string> *inner_inputs,
                               std::set<std::string> *inner_outputs);

  void AddDepToBlockOp(const BlockDesc &block);
};
void WriteToFile(const std::string &file_path, const std::string &msg);
void DumpProgramDescFile(const std::string &name, const ProgramDesc &program);
template <class V>
void DumpV(
    const V &v,
    const char *path,
    std::function<std::string(typename V::value_type)> f =
        [](typename V::value_type it) -> std::string { return it; }) {
  std::ostringstream str_os;
  for (auto it : v) {
    str_os << f(it) << std::endl;
  }
  std::ofstream ofs(path);
  ofs << str_os.str();
  ofs.close();
}
}  // namespace framework
}  // namespace paddle