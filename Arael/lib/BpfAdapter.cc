#include "BpfAdapter.h"

#include <stdexcept>

extern "C" {
#include <assert.h>
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

// Helper function, check file path include ".bpf.o" suffix.
bool suffixCheck(const std::string &fp) {
  return fp.length() >= 6 &&
         (fp.substr(fp.length() - 6, fp.length()) == ".bpf.o");
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
    loadBpfModule(module_path);
  }

  if (set_limit) {
    setBpfAdapterLimit()
  }
}

BpfAdapter::BpfAdapter(const std::filesystem::path &module_dir,
                       bool set_limit) {
  assert(std::filesystem::is_directory(module_dir));

  for (const auto &f : std::filesystem::directory_iterator(module_dir)) {
    loadBpfModule(static_cast<std::string>(f.path()));
  }

  if (set_limit) {
    setBpfAdapterLimit()
  }
}

int BpfAdapter::loadBpfModule(const std::string &module_path) {
  if (!suffixCheck(module_path) ||
      (bpf_modules_.find(module_path) != bpf_modules_.end())) {
    // TODO: Add log to record error.
    return 1;
  }

  std::unique_ptr<BpfModule> mod = make_unique<BpfModule>();
  const int err = loader_->openBpfFile(module_path, mod);
  if (err) {
    // TODO: Add log to record error.
    return 1;
  }

  bpf_modules_[module_path] = mod;
  return 0;
}

int BpfAdapter::attachBpfModule(const std::string &module_path) {
  auto mod = bpf_modules_.find(module_path);
  if (mod == bpf_modules_.end()) {
    // TODO: Add log to record error.
    return 1;
  }

  const int err = loader_->attachBpfProgs(mod);
  if (err) {
    // TODO: Add log to record error.
    return 1;
  }
  return 0;
}

int BpfAdapter::attachBpfProg(const std::string &module_path,
                              const std::string &prog_name) {
  auto mod = bpf_modules_.find(module_path);
  if (mod == bpf_modules_.end()) {
    // TODO: Add log to record error.
    return 1;
  }

  const int err = loader_->attachBpfProg(mod, prog_name);
  if (err) {
    // TODO: Add log to record error.
    return 1;
  }

  return 0;
}

int BpfAdapter::detachBpfModule(const std::string &module_path) {
  auto mod = bpf_modules_.find(module_path);
  if (mod == bpf_modules_.end()) {
    // TODO: Add log to record error.
    return 1;
  }

  const int err = loader_->detachBpfProg(mod);
  if (err) {
    // TODO: Add log to record error.
    return 1;
  }
  return 0;
}

int BpfAdapter::detachBpfProg(const std::string &module_path,
                              const std::string &prog_name) {
  auto mod = bpf_modules_.find(module_path);
  if (mod == bpf_modules_.end()) {
    // TODO: Add log to record error.
    return 1;
  }

  const int err = loader_->detachBpfProg(mod, prog_name);
  if (err) {
    // TODO: Add log to record error.
    return 1;
  }

  return 0;
}

}  // namespace arael