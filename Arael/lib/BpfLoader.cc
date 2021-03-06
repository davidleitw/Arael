#include "BpfLoader.h"

#include <iostream>
#include <string>

namespace {
constexpr int kError = 1;
constexpr int kSuccess = 0;
}  // namespace


namespace arael {

int BpfLoader::openBpfFile(const std::string &module_path, BpfModule &ctx) {
  auto obj = ::bpf_object__open(module_path.c_str());
  const int err = ::libbpf_get_error(obj);
  
  if (::libbpf_get_error(obj)) {
    // TODO: Add log to record error.
    return closeBpfFile(obj);
  }

  ctx.module_name = module_path;
  ctx.object = obj;
  return loadBpfFile(obj, ctx);
}

int BpfLoader::loadBpfFile(::bpf_object *obj, BpfModule &ctx) {
  ::bpf_program *prog;
  ::bpf_map *map;

  if (::bpf_object__load(obj)) {
    // TODO: Add log to record error.
    return closeBpfFile(obj);
  }

  bpf_object__for_each_program(prog, obj) {
    std::string prog_name(::bpf_program__name(prog));
    if (ctx.progs.find(prog_name) != ctx.progs.end()) {
      // TODO: Add log to record error.
      return closeBpfFile(obj);
    }
    ctx.progs[prog_name] = BpfProgStatus(prog, nullptr, false);
  }

  bpf_map__for_each(map, obj) {
    std::string map_name(::bpf_map__name(map));
    const int map_fd = ::bpf_map__fd(map);

    if (ctx.maps.find(map_name) != ctx.maps.end()) {
      // TODO: Add log to record error.
      return closeBpfFile(obj);
    }
    ctx.maps[map_name] = map_fd;
  }
  return kSuccess;
}

int BpfLoader::attachBpfProgs(BpfModule &ctx) {
  for (auto &program : ctx.progs) {
    program.second.link = ::bpf_program__attach(program.second.prog);
    if (::libbpf_get_error(program.second.link)) {
      // TODO: Add log to record error.
      program.second.link = nullptr;
      return kError;
    }
    program.second.is_attached = true;
  }
  return kSuccess;
}

int BpfLoader::attachBpfProg(BpfModule &ctx, const std::string &prog_name) {
  auto program = ctx.progs.find(prog_name);
  if (program == ctx.progs.end()) {
    // TODO: Add log to record error.
    return kError;
  }

  program->second.link = ::bpf_program__attach(program->second.prog);
  if (::libbpf_get_error(program->second.link)) {
    // TODO: Add log to record error.
    program->second.link = nullptr;
    return kError;
  }

  program->second.is_attached = true;
  return kSuccess;
}

int BpfLoader::detachBpfProgs(BpfModule &ctx) {
  for (auto &program : ctx.progs) {
    if (program.second.is_attached && program.second.link) {
      const int err = ::bpf_link__destroy(program.second.link);
      if (err) {
        // TODO: Add log to record error.
        return kError;
      }
      program.second.link = nullptr;
      program.second.is_attached = false;
    }
  }
  return kSuccess;
}

int BpfLoader::detachBpfProg(BpfModule &ctx, const std::string &prog_name) {
  auto program = ctx.progs.find(prog_name);
  if (program == ctx.progs.end()) {
    // TODO: Add log to record error.
    return kError;
  }

  if (program->second.is_attached && program->second.link) {
    const int err = ::bpf_link__destroy(program->second.link);
    if (err) {
      // TODO: Add log to record error.
      return kError;
    }
    program->second.link = nullptr;
    program->second.is_attached = false;
  }
  return kSuccess;
}

int BpfLoader::closeBpfFile(::bpf_object *obj) {
  ::bpf_object__close(obj);
  return kError;
}

}  // namespace arael