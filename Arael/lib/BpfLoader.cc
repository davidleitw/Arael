
#include <BpfLoader.h>

#include <string>

namespace {
constexpr int kError = 1;
constexpr int kSuccess = 0;
}  // namespace

namespace {}

namespace arael {

int BpfLoader::parseBpfModule(const std::string &module_path, BpfModule &ctx) {
  auto obj = ::bpf_object__open(module_path.c_str());
  const auto err = ::libbpf_get_error(obj);

  if (err) {
    // TODO: Add log to record error.
    return kError;
  }

  ctx.object = obj;
  return loadBpfModule(obj, ctx);
}

int BpfLoader::loadBpfModule(::bpf_object *obj, BpfModule &ctx) {
  ::bpf_program *prog;
  ::bpf_map *map;

  if (bpf_object__load(obj)) {
    // TODO: Add log to record error.
    return closeBpfModule(obj);
  }

  bpf_object__for_each_program(prog, obj) {
    std::string prog_name(::bpf_program__name(prog));
    if (ctx.progs.find(prog_name) != ctx.progs.end()) {
      // TODO: Add log to record error.
      return closeBpfModule(obj);
    }
    ctx.progs[prog_name] = -1;
  }

  bpf_map__for_each(map, obj) {
    std::string map_name(::bpf_map__name(map));
    if (ctx.maps.find(map_name) != ctx.maps.end()) {
      // TODO: Add log to record error.
      return closeBpfModule(obj);
    }
    ctx.maps[map_name] = -1;
  }

  return kSuccess;
}

int BpfLoader::closeBpfModule(::bpf_object *obj) {
  ::bpf_object__close(obj);
  return kError;
}

}  // namespace arael