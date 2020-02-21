//
// Created by Xiaofeng Qian on 21/2/20.
//
#include <gtest/gtest.h>
#include "eosvm_tester.hpp"


TEST_F(eosvm_tester, can_create){
  execute_contract(std::string("contract/add_project.wasm"));

  EXPECT_TRUE(1==1);
}