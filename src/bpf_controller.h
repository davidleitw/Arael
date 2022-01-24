#pragma once

#include <string>
#include <vector>
#include <map>

#include "bpf_module.h"

class BpfController {
public:
    BpfController(const std::vector<Bpf_Module*> &bpf_modules);
    ~BpfController();

private:
    // std::map<std::string, std::vector<std::string>> bpf_modules_;
    std::vector<Bpf_Module*> bpf_modules_;

    void load_bpf_module_names(const std::map<std::string, std::vector<std::string>> &bpf_modules);

    void bpf_probes_open();
    void bpf_probes_load();
    void bpf_probes_attach();
    void bpf_probes_destroy();
};
