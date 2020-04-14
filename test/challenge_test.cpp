//
// Created by Vince on 2/3/20.
//
#include <gtest/gtest.h>
#include "challenge_tester.hpp"
#include "../lib/vm.hpp"
#include "../lib/contract/challenge_contract.hpp"


TEST_F(challenge_tester, basic){
    REGISTER_CALLABLE_CLASS(vmtest::public_key, vmtest::public_key::serialize, vmtest::public_key::deserialize);
    REGISTER_CALLABLE_CLASS(vmtest::signature, vmtest::signature::serialize, vmtest::signature::deserialize);
    vm vm(challenge_wasm, "bpa"_n);

    vm.link_token({1397703940, "eosio.token"_n});

    vm.create("bpb"_n, "0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6");
    vm.create("bpc"_n, "cd1722f3947def4cf144679da39c4c32bdc35681");

    vm.set_storage("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", {"0x0000000000000000000000000000000000000000000000000000000000000000", "0x0000000000000000000000000000000000000000000000000000000000000004"});

    vm.print_tables();
//
    auto map = vm.rawtest(
            "0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6",
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x6023600a600850600054015660015b600255",
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