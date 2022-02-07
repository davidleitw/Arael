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
  BpfLoader() = default;

  int openBpfFile(const std::string &path, BpfModule &ctx);
  int loadBpfFile(::bpf_object *obj, BpfModule &ctx);

  int attachBpfProgs(BpfModule &ctx);
  int attachBpfProg(BpfModule &ctx, const std::string &prog_name);
  int detachBpfProgs(BpfModule &ctx);
  int detachBpfProg(BpfModule &ctx, const std::string &prog_name);

  int closeBpfFile(::bpf_object *obj);

 private:
};

}  // namespace arael