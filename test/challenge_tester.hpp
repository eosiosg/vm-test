//
// Created by Vince on 2/3/20.
//
#include <gtest/gtest.h>
#include "../lib/vm.hpp"
#include "../lib/contract/challenge_contract.hpp"

class challenge_tester : public testing::Test {
public:
    eosio::name contract = "eosevm111111"_n;
    eosio::name accountb = "eosevm11111b"_n;
    eosio::name accountc = "eosevm11111c"_n;
    eosio::name accountd = "eosevm11111d"_n;

//    void get_balance(eosio::name account);
};