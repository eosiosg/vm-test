//
// Created by Vince on 26/2/20.
//
#include <gtest/gtest.h>
#include "eosio_token_tester.hpp"


TEST_F(eosio_token_tester, transfer){
  execute_contract(std::string("contract/eosio.token/eosio.token.wasm"));

  EXPECT_TRUE(1==1);
}