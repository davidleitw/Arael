#pragma once

#include <filesystem>
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
  BpfAdapter(const std::filesystem::path &module_dir, bool set_limit = true);
  ~BpfAdapter();

  int loadBpfModule(const std::string &module_path);
  int reloadBpfModule(const std::string &module_path);

  int attachBpfModule(const std::string &module_path);
  int attachBpfProg(const std::string &module_path,
                    const std::string &prog_name);

  int detachBpfModule(const std::string &module_path);
  int detachBpfProg(const std::string &module_path,
                    const std::string &prog_name);

  // Destroy every bpf_link in bpf_object, and close bpf_object.
  int destroyBpfModule(const std::string &module_path);

 private:
  std::unique_ptr<BpfLoader> loader_;
  std::unordered_map<std::string, std::unique_ptr<BpfModule>> bpf_modules_;
}

}  // namespace arael