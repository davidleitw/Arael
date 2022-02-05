#pragma once

#include <string>
#include <unordered_map>
#include <vector>

extern "c" {
#include <bpf/libbpf.h>
}

namespace arael {

struct BpfProgStatus {
  ::bpf_program *prog;

  ::bpf_link *link;

  bool is_attached;

  BpfProgStatus(::bpf_program *p, ::bpf_link *l, bool attached)
      : prog(p), link(l), is_attached(attached){};
};

struct BpfModule {
  std::string module_name;

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
  std::unordered_map<std::string, BpfProgStatus> progs;
};

}  // namespace arael