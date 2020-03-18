//
// Created by Vince on 8/3/20.
//
#include <gtest/gtest.h>
#include "multi_index_tester.hpp"


TEST_F(multi_index_tester, basic) {
  execute_contract(std::string("contract/multi_index_example/multi_index_example.wasm"));

  EXPECT_TRUE(1==1);
}