//
// Created by Vince on 2/3/20.
//
#include <gtest/gtest.h>
#include "challenge_tester.hpp"


TEST_F(challenge_tester, basic){
  execute_contract(std::string("contract/challenge/test_contract.wasm"));

  EXPECT_TRUE(true);
}