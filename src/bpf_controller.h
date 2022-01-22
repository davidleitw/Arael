#pragma once

#include <string>
#include <vector>

class BpfController {
public:
    BpfController(std::vector<std::string> &probe_names);
    ~BpfController();

private:
    std::vector<std::string> probe_names_;
    std::vector<std::string> skel_names_;

    void load_ebpf_probe_names(std::vector<std::string> &probe_names);
};


