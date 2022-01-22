#include "bpf_controller.h"

BpfController::BpfController(std::vector<std::string> &probe_names) {
    load_ebpf_probe_names(probe_names);
}

BpfController::~BpfController() {
    
}

void BpfController::load_ebpf_probe_names(std::vector<std::string> &probe_names) {
    for (const auto &probe_name: probe_names) {
        probe_names_.push_back(probe_name);
        skel_names_.push_back(probe_name+".skel.h");
    }
}

