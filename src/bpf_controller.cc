#include "bpf_controller.h"
#include "bpf_module_list.h"



BpfController::BpfController(const std::vector<Bpf_Module*> &bpf_modules) {
    load_bpf_module_names(bpf_modules);

}

BpfController::~BpfController() {
    
}

void BpfController::load_bpf_module_names(const std::vector<Bpf_Module*> &bpf_modules) {
    bpf_modules_ = bpf_modules;
}


