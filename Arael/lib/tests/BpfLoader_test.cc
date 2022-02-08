#include "BpfLoader.h"

#include <gtest/gtest.h>

#include <iostream>

// clang++ BpfLoader_test.cc -lgtest -lpthread -lelf -lz -I ../ -I
// ../bpf/.output/ ../bpf/.output/libbpf.a -o test

int main() {
  std::cout << "Hello world" << std::endl;

  return 0;
}