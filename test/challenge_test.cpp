//
// Created by Vince on 2/3/20.
//
#include <gtest/gtest.h>
#include "challenge_tester.hpp"
#include "../lib/vm.hpp"


TEST_F(challenge_tester, basic){
  REGISTER_CALLABLE_CLASS(sz::public_key, sz::public_key::serialize, sz::public_key::deserialize);
  REGISTER_CALLABLE_CLASS(sz::signature, sz::signature::serialize, sz::signature::deserialize);
    vm vm(std::string("contract/challenge/eos_evm.wasm"), "bpa"_n);

    vm.link_token({1397703940, "eosio.token"_n});

    vm.create("bpb"_n, "0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6");
    vm.create("bpc"_n, "cd1722f3947def4cf144679da39c4c32bdc35681");

    vm.print_tables();

    auto map = vm.rawtest(
            "0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6",
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x435660615b4343025660615b60615b5b5b6001600155",
            "0x",
            "0x0186a0",
            "0x5af3107a4000",
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x0de0b6b3a7640000"
            );

    vm.print_tables();

    auto v = vm.get_addresses();
    for (auto& e: v) {
        auto m = vm.get_storage(e);
        cout << m.size();
    }
    auto m1 = vm.get_storage("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6");
    auto m2 = vm.get_storage("0xcd1722f3947def4cf144679da39c4c32bdc35681");
    auto m3 = vm.get_storage("0xbbccddeeff00112233445566778899aabbccddee");

  EXPECT_TRUE(true);
}