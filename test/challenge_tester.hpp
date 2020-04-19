//
// Created by Vince on 2/3/20.
//
#include <gtest/gtest.h>
#include "../lib/vm.hpp"
#include "../lib/contract/challenge_contract.hpp"

struct account_type {
    string address = "0x";
    string balance = "0x";
    string code = "0x";
    string nonce = "0x";

    inline bool operator==(const account_type& rhs) const
    {
        return std::tie(address, balance, code, nonce)
        == std::tie(rhs.address, rhs.balance, rhs.code, rhs.nonce);
    }
};

class challenge_tester : public testing::Test {
public:
    challenge_tester(): eosevm(challenge_wasm, contract) {
        eosevm.link_token({1397703940, "eosio.token"_n});
        REGISTER_CALLABLE_CLASS(vmtest::public_key, vmtest::public_key::serialize, vmtest::public_key::deserialize);
        REGISTER_CALLABLE_CLASS(vmtest::signature, vmtest::signature::serialize, vmtest::signature::deserialize);
    }
    constexpr static eosio::name contract = "eosevm111111"_n;
    constexpr static eosio::name accountb = "eosevm11111b"_n;
    constexpr static eosio::name accountc = "eosevm11111c"_n;
    constexpr static eosio::name accountd = "eosevm11111d"_n;
    vm eosevm;

    account_type get_account(const string& addr) {
        account_type ret;
        auto key = eosevm.eth_address_to_key256(addr);
        auto value = eosevm.get_table_rows(contract, "account"_n, eosevm.find_primary_by_key256(key));
        if (!value.empty()) {
            ret.address += string(value.data() + 16, value.data() + 56);
            ret.nonce += string(value.data() + 56, value.data() + 120);
            ret.balance += string(value.data() + 120, value.data() + 184);
        }
        return ret;
    }
};