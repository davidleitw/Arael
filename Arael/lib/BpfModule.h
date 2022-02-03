#pragma once

#include <string>
#include <unordered_map>
#include <vector>

extern "c" {
#include <bpf/libbpf.h>
}

namespace arael {

struct BpfModule {
  /**
   * Pointer to bpf_object.
   */
  ::bpf_object *object;
  /**
   * Dict of map's name to map's descriptor.
   */
  std::unordered_map<std::string, int> maps;
  /*
   * Dict of prog's name to prog's descriptor.
   */
  std::unordered_map<std::string, int> progs;
};

}  // namespace arael