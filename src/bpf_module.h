#pragma once

#include <string>
#include <vector>

#define DEFINE_BPF_SKEL(module_name) \
    struct module_name##_bpf *module_name##_skel; 

/*
    * reference: https://en.pingcap.com/blog/tips-and-tricks-for-writing-linux-bpf-applications-with-libbpf/
    * You can call <name>__open_and_load() to combine the two phases into one.
    * It makes our code look more compact.
*/
#define OPEN_AND_LOAD_BPF_MODULE(module_name, skel_name) \
    module_name##_skel = module_name##_bpf__open_and_load()

#define OPEN_BPF_MODULE(module_name) \
    module_name##_skel = module_name##_bpf__open()

#define LOAD_BPF_MODULE(module_name) \
    module_name##_bpf__load(module_name##_skel)

#define ATTACH_BPF_PROG(module_name, prog_name) \
    module_name##_skel->links.prog_name = bpf_program__attach(module_name##_skel->progs.prog_name)

#define GET_ERR_WITH_ATTACH(module_name, prog_name) \
    libbpf_get_error(module_name##_skel->links.##progname)

#define DESTROY_BPF_MODULE(module_name) \
    module_name##_bpf__destroy(module_name##_skel)

#define BPF_SKEL(module_name) \
    module_name##_skel 

class Bpf_Module {
public:
    Bpf_Module(const std::string &module_name, const std::vector<std::string> &progs);
    virtual ~Bpf_Module();

    virtual void BpfModuleOpen();
    virtual void BpfModuleLoad();
    virtual void BpfModuleAttach();
    virtual void BpfModuleDetach();
    virtual void BpfModuleDestroy();
private:
    std::string module_name_;
    std::vector<std::string> progs_;
};