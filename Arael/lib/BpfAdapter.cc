#include "BpfAdapter.h"

#include <stdexcept>

extern "C" {
#include <sys/resource.h>
}

namespace {

void setBpfAdapterLimit() {
  struct rlimit limit = {};
  limit.rlim_cur = RLIM_INFINITY;
  limit.rlim_max = RLIM_INFINITY;

  if (set_limit(RLIMIT_MEMLOCK, &limit)) {
    // TODO: Add log to record error.
    throw std::runtime_error("Error with setting limited locked memory.");
  }
}

}  // namespace

namespace arael {

BpfAdapter::BpfAdapter(bool set_limit) {
  if (set_limit) {
    setBpfAdapterLimit();
  }
}

BpfAdapter::BpfAdapter(const std::vector<std::string> &module_paths,
                       bool set_limit) {
  loader_ = make_unique<BpfLoader>();

  for (const auto &module_path) {
    RegisterBpfModule(module_path);
  }

  if (set_limit) {
    setBpfAdapterLimit()
  }
}

int BpfAdapter::RegisterBpfModule(const std::string &module_path) {
  // Already exist same module path.
  if (bpf_modules_.find(module_path) != bpf_modules_.end()) {
    // TODO: Add log to record error.
    return 1;
  }

  std::unique_ptr<BpfModule> mod = make_unique<BpfModule>();
  if (loader_->parseBpfModulePath(module_path, mod)) {
    // TODO: Add log to record error.
    return 1;
  }

  bpf_modules_[module_path] = mod;
  return 0;
}

int BpfAdapter::RegisterBpfModules(
    const std::vector<std::string> &module_paths) {
  for (const auto &module_path) {
    if (RegisterBpfModule(module_path)) {
      // TODO: Add log to record error.
      return 1;
    }
  }
  return 0;
}

}  // namespace arael