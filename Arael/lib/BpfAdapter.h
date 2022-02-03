#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "BpfLoader.h"
#include "BpfModule.h"

extern "C" {
#include <bpf/bpf.h>
}

namespace arael {

class BpfAdapter {
 public:
  BpfAdapter(bool set_limit = true);
  BpfAdapter(const std::vector<std::string> &module_paths,
             bool set_limit = true);
  ~BpfAdapter();

  int RegisterBpfModule(const std::string &module_path);
  int RegisterBpfModules(const std::vector<std::string> &module_paths);

 private:
  std::unique_ptr<BpfLoader> loader_;
  std::unordered_map<std::string, std::unique_ptr<BpfModule>> bpf_modules_;
}

}  // namespace arael