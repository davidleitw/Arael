#pragma once

#include <string>
#include <unordered_map>
#include <vector>

extern "C" {
#include <bpf/libbpf.h>
}

namespace arael {

struct BpfProgStatus {
  ::bpf_program *prog;

  ::bpf_link *link;
  
  bool is_attached;

  BpfProgStatus() = default;
  BpfProgStatus(::bpf_program *p, ::bpf_link *l, bool attached)
      : prog(p), link(l), is_attached(attached){};
};

struct BpfModule {
  ~BpfModule() {
    for (auto prog : progs) {
      if (prog.second.link) {
        ::bpf_link__destroy(prog.second.link);
      }
    }
    ::bpf_object__close(object);
  }
  /**
   * BpfModule use the path of bpf object file as module_name
   */
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