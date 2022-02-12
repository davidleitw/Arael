#include "BpfLoader.h"

#include <gtest/gtest.h>

#include <iostream>
#include <string>

TEST(TestBpfLoader, TestBpfLoaderOpenFileExistAndFit) {
  arael::BpfLoader loader;
  arael::BpfModule mod;

  std::string input_path("bootstrap.bpf.o");
  int res = loader.openBpfFile(input_path, mod);
  std::cout << res << std::endl;
  EXPECT_EQ(res, 0);
}

TEST(TestBpfLoader, TestBpfLoaderOpenFileExistButNotFit) {
  arael::BpfLoader loader;
  arael::BpfModule mod;

  std::string input_path("BpfLoader_test.cc");
  int res = loader.openBpfFile(input_path, mod);
  std::cout << res << std::endl;
  ASSERT_EQ(res, 1);
}

// clang++ -std=c++17 BpfLoader_test.cc -lgtest -lpthread -lelf -lz
// ../bpf/.output/libbpf.a -I ../bpf/.output ../BpfLoader.o -I ../ -o
// BpfLoader_test

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}