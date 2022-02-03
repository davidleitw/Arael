#pragma once

#include <string>
#include <vector>

#include "BpfModule.h"

extern "C" {
#include <bpf/libbpf.h>
}

namespace arael {

class BpfLoader {
 public:
  BpfLoader() = {};

  int parseBpfModulePath(const std::string &path, BpfModule &ctx);
  int loadBpfModule(::bpf_object *obj, BpfModule &ctx);
  int closeBpfModule(::bpf_object *obj);

 private:
};

}  // namespace arael