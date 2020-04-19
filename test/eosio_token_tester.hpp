//
// Created by Vince on 26/2/20.
//
#include <gtest/gtest.h>
#include "../lib/vm.hpp"
#include "../lib/contract/eosio_token_contract.hpp"

struct create {
    eosio::name issuer;
    asset       maximum_supply;

    void pack(vector<char>& dest) {
        dest.resize(sizeof(issuer)+sizeof(maximum_supply));
        memcpy(&dest[0], &issuer , sizeof(issuer));
        memcpy(&dest[sizeof(issuer)], &maximum_supply , sizeof(maximum_supply));
    }
};

struct issue {
    eosio::name to;
    asset       quantity;
    string      memo;

    void pack(vector<char>& dest) {
        dest.resize(sizeof(to)+sizeof(quantity));
        memcpy(&dest[0], &to , sizeof(to ));
        memcpy(&dest[sizeof(to)], &quantity , sizeof(quantity));
        pack_string(memo, dest);
    }
};

struct transfer {
    eosio::name from;
    eosio::name to;
    asset       amount;
    string      memo;

    void pack(vector<char>& dest) {
        dest.resize(sizeof(from)+sizeof(to)+sizeof(amount));
        memcpy(&dest[0], &to , sizeof(to ));
        memcpy(&dest[sizeof(from)], &to , sizeof(to ));
        memcpy(&dest[sizeof(from)+sizeof(to)], &amount , sizeof(amount ));
        pack_string(memo, dest);
    }
};

struct balance {
    asset amount;
};

class eosio_token_tester : public testing::Test {
protected:
    eosio_token_tester(): eosevm(token_wasm, contract) {
        REGISTER_CALLABLE_CLASS(vmtest::public_key, vmtest::public_key::serialize, vmtest::public_key::deserialize);
        REGISTER_CALLABLE_CLASS(vmtest::signature, vmtest::signature::serialize, vmtest::signature::deserialize);
    }
    constexpr static eosio::name contract = "eosio.token"_n;
    constexpr static eosio::name alice = "alice"_n;
    constexpr static eosio::name bob = "bob"_n;
    vm eosevm;

    balance get_balance(eosio::name acc) {
        balance ret;
        auto row = eosevm.get_table_rows(contract, "accounts"_n, acc.value);
        ret = {string_to_i64(string(row.data()+16, row.data()+32)),
               string_to_ui64(string(row.data()+32, row.data()+48))
        };
        return ret;
    }
};