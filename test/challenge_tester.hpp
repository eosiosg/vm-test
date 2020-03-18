//
// Created by Vince on 2/3/20.
//

#include <eosio/vm/backend.hpp>
#include <eosio/vm/watchdog.hpp>
#include <eosio/vm/execution_context.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include "name.hpp"
#include "mocked_context.hpp"
#include "utils.hpp"
#include <openssl/sha.h>

typedef string eth_addr;
typedef string hex_code;
typedef string sha256_type;
typedef uint64_t name;



using backend_t = eosio::vm::backend<mocked_context>;
using rhf_t = eosio::vm::registered_host_functions<mocked_context>;

class challenge_tester : public testing::Test {
protected:
    void execute_contract(const std::string &path) {

        std::ifstream input(path, std::ios::binary | std::ios::ate);
        std::ifstream::pos_type pos = input.tellg();
        std::vector<char> tmp(pos);
        input.seekg(0, std::ios::beg);
        input.read(&tmp[0], pos);

        std::vector<uint8_t> wasm;

        std::copy(tmp.begin(), tmp.end(), std::back_inserter(wasm));

        backend_t backend(wasm);

        eosio::vm::wasm_allocator wa;
        eosio::vm::watchdog wd{std::chrono::seconds(3000000)};
        // Point the backend to the allocator you want it to use.
        backend.set_wasm_allocator(&wa);
        backend.initialize();
        // Resolve the host functions indices.
        db_type database;
        secondary_key_type<uint64_t > i64_index;
        secondary_key_type<array<uint128_t, 2>> i256_index;
        vector<kv_type> keyval_cache{};
        vector<i64_sec_kv_type> i64_sec_keyval_cache{};
        vector<i256_sec_kv_type> i256_sec_keyval_cache{};

        rhf_t::template add<mocked_context, &mocked_context::abort, eosio::vm::wasm_allocator>("env", "abort");
        rhf_t::template add<mocked_context, &mocked_context::eosio_assert, eosio::vm::wasm_allocator>("env", "eosio_assert");
        rhf_t::template add<mocked_context, &mocked_context::memset, eosio::vm::wasm_allocator>("env", "memset");
        rhf_t::template add<mocked_context, &mocked_context::memcpy, eosio::vm::wasm_allocator>("env", "memcpy");
        rhf_t::template add<mocked_context, &mocked_context::memmove, eosio::vm::wasm_allocator>("env", "memmove");
        rhf_t::template add<mocked_context, &mocked_context::__extendsftf2, eosio::vm::wasm_allocator>("env", "__extendsftf2");
        rhf_t::template add<mocked_context, &mocked_context::__floatsitf, eosio::vm::wasm_allocator>("env", "__floatsitf");
        rhf_t::template add<mocked_context, &mocked_context::__multf3, eosio::vm::wasm_allocator>("env", "__multf3");
        rhf_t::template add<mocked_context, &mocked_context::__floatunsitf, eosio::vm::wasm_allocator>("env", "__floatunsitf");
        rhf_t::template add<mocked_context, &mocked_context::__divtf3, eosio::vm::wasm_allocator>("env", "__divtf3");
        rhf_t::template add<mocked_context, &mocked_context::__addtf3, eosio::vm::wasm_allocator>("env", "__addtf3");
        rhf_t::template add<mocked_context, &mocked_context::__extenddftf2, eosio::vm::wasm_allocator>("env", "__extenddftf2");
        rhf_t::template add<mocked_context, &mocked_context::__eqtf2, eosio::vm::wasm_allocator>("env", "__eqtf2");
        rhf_t::template add<mocked_context, &mocked_context::__letf2, eosio::vm::wasm_allocator>("env", "__letf2");
        rhf_t::template add<mocked_context, &mocked_context::__netf2, eosio::vm::wasm_allocator>("env", "__netf2");
        rhf_t::template add<mocked_context, &mocked_context::__subtf3, eosio::vm::wasm_allocator>("env", "__subtf3");
        rhf_t::template add<mocked_context, &mocked_context::__trunctfdf2, eosio::vm::wasm_allocator>("env", "__trunctfdf2");
        rhf_t::template add<mocked_context, &mocked_context::__getf2, eosio::vm::wasm_allocator>("env", "__getf2");
        rhf_t::template add<mocked_context, &mocked_context::__trunctfsf2, eosio::vm::wasm_allocator>("env", "__trunctfsf2");
        rhf_t::template add<mocked_context, &mocked_context::prints_l, eosio::vm::wasm_allocator>("env", "prints_l");
        rhf_t::template add<mocked_context, &mocked_context::__unordtf2, eosio::vm::wasm_allocator>("env", "__unordtf2");
        rhf_t::template add<mocked_context, &mocked_context::__fixunstfsi, eosio::vm::wasm_allocator>("env", "__fixunstfsi");
        rhf_t::template add<mocked_context, &mocked_context::__fixtfsi, eosio::vm::wasm_allocator>("env", "__fixtfsi");
        rhf_t::template add<mocked_context, &mocked_context::__ashlti3, eosio::vm::wasm_allocator>("env", "__ashlti3");
        rhf_t::template add<mocked_context, &mocked_context::require_auth, eosio::vm::wasm_allocator>("env", "require_auth");
        rhf_t::template add<mocked_context, &mocked_context::db_lowerbound_i64, eosio::vm::wasm_allocator>("env", "db_lowerbound_i64");
        rhf_t::template add<mocked_context, &mocked_context::current_receiver, eosio::vm::wasm_allocator>("env", "current_receiver");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_lowerbound, eosio::vm::wasm_allocator>("env", "db_idx256_lowerbound");
        rhf_t::template add<mocked_context, &mocked_context::db_find_i64, eosio::vm::wasm_allocator>("env", "db_find_i64");
        rhf_t::template add<mocked_context, &mocked_context::assert_sha256, eosio::vm::wasm_allocator>("env", "assert_sha256");
        rhf_t::template add<mocked_context, &mocked_context::assert_sha1, eosio::vm::wasm_allocator>("env", "assert_sha1");
        rhf_t::template add<mocked_context, &mocked_context::assert_sha512, eosio::vm::wasm_allocator>("env", "assert_sha512");
        rhf_t::template add<mocked_context, &mocked_context::assert_ripemd160, eosio::vm::wasm_allocator>("env", "assert_ripemd160");
        rhf_t::template add<mocked_context, &mocked_context::sha256, eosio::vm::wasm_allocator>("env", "sha256");
        rhf_t::template add<mocked_context, &mocked_context::sha1, eosio::vm::wasm_allocator>("env", "sha1");
        rhf_t::template add<mocked_context, &mocked_context::sha512, eosio::vm::wasm_allocator>("env", "sha512");
        rhf_t::template add<mocked_context, &mocked_context::ripemd160, eosio::vm::wasm_allocator>("env", "ripemd160");
        rhf_t::template add<mocked_context, &mocked_context::recover_key, eosio::vm::wasm_allocator>("env", "recover_key");
        rhf_t::template add<mocked_context, &mocked_context::set_blockchain_parameters_packed, eosio::vm::wasm_allocator>("env", "set_blockchain_parameters_packed");
        rhf_t::template add<mocked_context, &mocked_context::get_blockchain_parameters_packed, eosio::vm::wasm_allocator>("env", "get_blockchain_parameters_packed");
        rhf_t::template add<mocked_context, &mocked_context::set_proposed_producers, eosio::vm::wasm_allocator>("env", "set_proposed_producers");
        rhf_t::template add<mocked_context, &mocked_context::current_time, eosio::vm::wasm_allocator>("env", "current_time");
        rhf_t::template add<mocked_context, &mocked_context::get_active_producers, eosio::vm::wasm_allocator>("env", "get_active_producers");
        rhf_t::template add<mocked_context, &mocked_context::assert_recover_key, eosio::vm::wasm_allocator>("env", "assert_recover_key");
        rhf_t::template add<mocked_context, &mocked_context::prints, eosio::vm::wasm_allocator>("env", "prints");
        rhf_t::template add<mocked_context, &mocked_context::printhex, eosio::vm::wasm_allocator>("env", "printhex");
        rhf_t::template add<mocked_context, &mocked_context::printui, eosio::vm::wasm_allocator>("env", "printui");
        rhf_t::template add<mocked_context, &mocked_context::db_store_i64, eosio::vm::wasm_allocator>("env", "db_store_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_update_i64, eosio::vm::wasm_allocator>("env", "db_update_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_find_primary, eosio::vm::wasm_allocator>("env", "db_idx256_find_primary");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_update, eosio::vm::wasm_allocator>("env", "db_idx256_update");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_find_primary, eosio::vm::wasm_allocator>("env", "db_idx64_find_primary");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_update, eosio::vm::wasm_allocator>("env", "db_idx64_update");
        rhf_t::template add<mocked_context, &mocked_context::send_inline, eosio::vm::wasm_allocator>("env", "send_inline");
        rhf_t::template add<mocked_context, &mocked_context::printi, eosio::vm::wasm_allocator>("env", "printi");
        rhf_t::template add<mocked_context, &mocked_context::action_data_size, eosio::vm::wasm_allocator>("env", "action_data_size");
        rhf_t::template add<mocked_context, &mocked_context::read_action_data, eosio::vm::wasm_allocator>("env", "read_action_data");
        rhf_t::template add<mocked_context, &mocked_context::eosio_assert_code, eosio::vm::wasm_allocator>("env", "eosio_assert_code");
        rhf_t::template add<mocked_context, &mocked_context::tapos_block_num, eosio::vm::wasm_allocator>("env", "tapos_block_num");
        rhf_t::template add<mocked_context, &mocked_context::db_get_i64, eosio::vm::wasm_allocator>("env", "db_get_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_store, eosio::vm::wasm_allocator>("env", "db_idx256_store");
        rhf_t::template add<mocked_context, &mocked_context::db_previous_i64, eosio::vm::wasm_allocator>("env", "db_previous_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_end_i64, eosio::vm::wasm_allocator>("env", "db_end_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_next, eosio::vm::wasm_allocator>("env", "db_idx256_next");
        rhf_t::template add<mocked_context, &mocked_context::db_remove_i64, eosio::vm::wasm_allocator>("env", "db_remove_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_remove, eosio::vm::wasm_allocator>("env", "db_idx256_remove");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_remove, eosio::vm::wasm_allocator>("env", "db_idx64_remove");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_store, eosio::vm::wasm_allocator>("env", "db_idx64_store");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_lowerbound, eosio::vm::wasm_allocator>("env", "db_idx64_lowerbound");
        rhf_t::template add<mocked_context, &mocked_context::__multi3, eosio::vm::wasm_allocator>("env", "__multi3");

        rhf_t::resolve(backend.get_module());

        // check action
        struct extended_symbol {
            uint64_t sym;
            uint64_t contract;
        };
        struct settoken_act {
            extended_symbol contract;
            void pack(vector<char>& dest) {
                    dest.resize(sizeof(contract));
                    memcpy(&dest[0], &contract , sizeof(contract ));
            }
        };
        auto && set_token = settoken_act{1397703940, 6138663591592764928};
        auto && set_token_data = bytes();
        set_token.pack(set_token_data);
        mocked_context set_token_ctx("bpa"_n.value, "bpa"_n.value, "settoken"_n.value, set_token_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn1 = [&]() {
            backend.initialize(&set_token_ctx);
            const auto& res = backend.call(
                    &set_token_ctx, "env", "apply", set_token_ctx.get_receiver(),
                    set_token_ctx.get_account(),
                    set_token_ctx.get_action());
        };
        backend.timed_run(wd, fn1);

        // create action
        struct create_act {
            uint64_t eos_account;
            string   salt;
            void pack(vector<char>& dest) {
                dest.resize(sizeof(eos_account));
                memcpy(&dest[0], &eos_account , sizeof(eos_account ));
                auto size = salt.size();
                uint64_t val = size;
                do {
                    uint8_t b = uint8_t(val) & 0x7f;
                    val >>= 7;
                    b |= ((val > 0) << 7);
                    dest.emplace_back(b);
                }while( val );
                copy(salt.begin(), salt.end(), back_inserter<vector<char> >(dest));
            }
        };
        auto && create_bpb = create_act{"bpb"_n.value, "aaaaaa"};
        auto && create_bpb_data = bytes();
        create_bpb.pack(create_bpb_data);
        mocked_context create_bpb_ctx("bpa"_n.value, "bpa"_n.value, "create"_n.value, create_bpb_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn2 = [&]() {
            backend.initialize(&create_bpb_ctx);
            const auto& res = backend.call(
                    &create_bpb_ctx, "env", "apply", create_bpb_ctx.get_receiver(),
                    create_bpb_ctx.get_account(),
                    create_bpb_ctx.get_action());
        };
        backend.timed_run(wd, fn2);

        auto && create_bpc = create_act{"bpc"_n.value, "aaaaaa"};
        auto && create_bpc_data = bytes();
        create_bpc.pack(create_bpc_data);
        mocked_context create_bpc_ctx("bpa"_n.value, "bpa"_n.value, "create"_n.value, create_bpc_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn3 = [&]() {
            backend.initialize(&create_bpc_ctx);
            const auto& res = backend.call(
                    &create_bpc_ctx, "env", "apply", create_bpc_ctx.get_receiver(),
                    create_bpc_ctx.get_account(),
                    create_bpc_ctx.get_action());
        };
        backend.timed_run(wd, fn3);

        auto && create_bpd = create_act{"bpd"_n.value, "aaaaaa"};
        auto && create_bpd_data = bytes();
        create_bpd.pack(create_bpd_data);
        mocked_context create_bpd_ctx("bpa"_n.value, "bpa"_n.value, "create"_n.value, create_bpd_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn4 = [&]() {
            backend.initialize(&create_bpd_ctx);
            const auto& res = backend.call(
                    &create_bpd_ctx, "env", "apply", create_bpd_ctx.get_receiver(),
                    create_bpd_ctx.get_account(),
                    create_bpd_ctx.get_action());
        };
        backend.timed_run(wd, fn4);

        // updateeth action
        struct createeth_act {
            name        eos_account;
            sha256_type eth_address;
            void pack(vector<char>& dest) {
                dest.resize(sizeof(eos_account));
                memcpy(&dest[0], &eos_account , sizeof(eos_account ));
                auto size = eth_address.size();
                uint64_t val = size;
                do {
                    uint8_t b = uint8_t(val) & 0x7f;
                    val >>= 7;
                    b |= ((val > 0) << 7);
                    dest.emplace_back(b);
                }while( val );
                copy(eth_address.begin(), eth_address.end(), back_inserter<vector<char> >(dest));
            }
        };
        auto && createeth_bpb = createeth_act{"bpb"_n.value, "d81f4358cb8cab53d005e7f47c7ba3f5116000a6"};
        auto && createeth_bpb_data = bytes();
        createeth_bpb.pack(createeth_bpb_data);
        mocked_context createeth_bpb_ctx("bpa"_n.value, "bpa"_n.value, "createeth"_n.value, createeth_bpb_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn5 = [&]() {
            backend.initialize(&createeth_bpb_ctx);
            const auto& res = backend.call(
                    &createeth_bpb_ctx, "env", "apply", createeth_bpb_ctx.get_receiver(),
                    createeth_bpb_ctx.get_account(),
                    createeth_bpb_ctx.get_action());
        };
        backend.timed_run(wd, fn5);

        auto && createeth_bpc = createeth_act{"bpc"_n.value, "39944247c2edf660d86d57764b58d83b8eee9014"};
        auto && createeth_bpc_data = bytes();
        createeth_bpc.pack(createeth_bpc_data);
        mocked_context createeth_bpc_ctx("bpa"_n.value, "bpa"_n.value, "createeth"_n.value, createeth_bpc_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn6 = [&]() {
            backend.initialize(&createeth_bpc_ctx);
            const auto& res = backend.call(
                    &createeth_bpc_ctx, "env", "apply", createeth_bpc_ctx.get_receiver(),
                    createeth_bpc_ctx.get_account(),
                    createeth_bpc_ctx.get_action());
        };
        backend.timed_run(wd, fn6);

        auto && createeth_bpd = createeth_act{"bpd"_n.value, "e327e755438fbdf9e60891d9b752da10a38514d1"};
        auto && createeth_bpd_data= bytes();
        createeth_bpd.pack(createeth_bpd_data);
        mocked_context createeth_bpd_ctx("bpa"_n.value, "bpa"_n.value, "createeth"_n.value, createeth_bpd_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn7 = [&]() {
            backend.initialize(&createeth_bpd_ctx);
            const auto& res = backend.call(
                    &createeth_bpd_ctx, "env", "apply", createeth_bpd_ctx.get_receiver(),
                    createeth_bpd_ctx.get_account(),
                    createeth_bpd_ctx.get_action());
        };
        backend.timed_run(wd, fn7);

        struct raw_act {
            hex_code trx_code;
            eth_addr sender;
            void pack(vector<char>& dest) {
                auto size = trx_code.size();
                uint64_t val = size;
                do {
                    uint8_t b = uint8_t(val) & 0x7f;
                    val >>= 7;
                    b |= ((val > 0) << 7);
                    dest.emplace_back(b);
                }while( val );
                copy(trx_code.begin(), trx_code.end(), back_inserter<vector<char> >(dest));
                dest.resize(dest.size()+20);
            }
        };
        auto && raw_create_token = raw_act{};
        raw_create_token.trx_code = "f90f25028609184e72a000830271008080b90ed16060604052341561000f57600080fd5b604051610dd1380380610dd18339810160405280805190602001909190805182019190602001805190602001909190805182019190505083600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508360008190555082600390805190602001906100a79291906100e3565b5081600460006101000a81548160ff021916908360ff16021790555080600590805190602001906100d99291906100e3565b5050505050610188565b828054600181600116156101000203166002900490600052602060002090601f016020900481019282601f1061012457805160ff1916838001178555610152565b82800160010185558215610152579182015b82811115610151578251825591602001919060010190610136565b5b50905061015f9190610163565b5090565b61018591905b80821115610181576000816000905550600101610169565b5090565b90565b610c3a806101976000396000f3006060604052600436106100af576000357c0100000000000000000000000000000000000000000000000000000000900463ffffffff16806306fdde03146100b4578063095ea7b31461014257806318160ddd1461019c57806323b872dd146101c557806327e235e31461023e578063313ce5671461028b5780635c658165146102ba57806370a082311461032657806395d89b4114610373578063a9059cbb14610401578063dd62ed3e1461045b575b600080fd5b34156100bf57600080fd5b6100c76104c7565b6040518080602001828103825283818151815260200191508051906020019080838360005b838110156101075780820151818401526020810190506100ec565b50505050905090810190601f1680156101345780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b341561014d57600080fd5b610182600480803573ffffffffffffffffffffffffffffffffffffffff16906020019091908035906020019091905050610565565b604051808215151515815260200191505060405180910390f35b34156101a757600080fd5b6101af610657565b6040518082815260200191505060405180910390f35b34156101d057600080fd5b610224600480803573ffffffffffffffffffffffffffffffffffffffff1690602001909190803573ffffffffffffffffffffffffffffffffffffffff1690602001909190803590602001909190505061065d565b604051808215151515815260200191505060405180910390f35b341561024957600080fd5b610275600480803573ffffffffffffffffffffffffffffffffffffffff169060200190919050506108f7565b6040518082815260200191505060405180910390f35b341561029657600080fd5b61029e61090f565b604051808260ff1660ff16815260200191505060405180910390f35b34156102c557600080fd5b610310600480803573ffffffffffffffffffffffffffffffffffffffff1690602001909190803573ffffffffffffffffffffffffffffffffffffffff16906020019091905050610922565b6040518082815260200191505060405180910390f35b341561033157600080fd5b61035d600480803573ffffffffffffffffffffffffffffffffffffffff16906020019091905050610947565b6040518082815260200191505060405180910390f35b341561037e57600080fd5b610386610990565b6040518080602001828103825283818151815260200191508051906020019080838360005b838110156103c65780820151818401526020810190506103ab565b50505050905090810190601f1680156103f35780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b341561040c57600080fd5b610441600480803573ffffffffffffffffffffffffffffffffffffffff16906020019091908035906020019091905050610a2e565b604051808215151515815260200191505060405180910390f35b341561046657600080fd5b6104b1600480803573ffffffffffffffffffffffffffffffffffffffff1690602001909190803573ffffffffffffffffffffffffffffffffffffffff16906020019091905050610b87565b6040518082815260200191505060405180910390f35b60038054600181600116156101000203166002900480601f01602080910402602001604051908101604052809291908181526020018280546001816001161561010002031660029004801561055d5780601f106105325761010080835404028352916020019161055d565b820191906000526020600020905b81548152906001019060200180831161054057829003601f168201915b505050505081565b600081600260003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925846040518082815260200191505060405180910390a36001905092915050565b60005481565b600080600260008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054905082600160008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020541015801561072e5750828110155b151561073957600080fd5b82600160008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000206000828254019250508190555082600160008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825403925050819055507fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff8110156108865782600260008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825403925050819055505b8373ffffffffffffffffffffffffffffffffffffffff168573ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef856040518082815260200191505060405180910390a360019150509392505050565b60016020528060005260406000206000915090505481565b600460009054906101000a900460ff1681565b6002602052816000526040600020602052806000526040600020600091509150505481565b6000600160008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020549050919050565b60058054600181600116156101000203166002900480601f016020809104026020016040519081016040528092919081815260200182805460018160011615610100020316600290048015610a265780601f106109fb57610100808354040283529160200191610a26565b820191906000526020600020905b815481529060010190602001808311610a0957829003601f168201915b505050505081565b600081600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205410151515610a7e57600080fd5b81600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000206000828254039250508190555081600160008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825401925050819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef846040518082815260200191505060405180910390a36001905092915050565b6000600260008473ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020549050929150505600a165627a7a72305820c4fde1a7c25d01c2c831892bb28af4a76928a6ac10d854b6e98b38d49891c19c002900000000000000000000000000000000000000000000000000000000000027100000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000000000000000000000000000000000000000000566697273740000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000005457468657200000000000000000000000000000000000000000000000000000025a067efd6d3fc643c3dde86ef3634da7c120abe8b684cfe67e2e07094b8bc959400a018d29628aff2b72cf5807a0068429a670dbc86be9850f89bae6a11af910d407b";
        raw_create_token.sender = "";
        auto && raw_create_token_data = bytes();
        raw_create_token.pack(raw_create_token_data);
        mocked_context raw_create_token_ctx("bpa"_n.value, "bpa"_n.value, "raw"_n.value, raw_create_token_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn10 = [&]() {
            backend.initialize(&raw_create_token_ctx);
            const auto& res = backend.call(
                    &raw_create_token_ctx, "env", "apply", raw_create_token_ctx.get_receiver(),
                    raw_create_token_ctx.get_account(),
                    raw_create_token_ctx.get_action());
        };
        backend.timed_run(wd, fn10);

        // transfer bpc 100
        auto && raw_transfer_bpc = raw_act{};
        raw_transfer_bpc.trx_code = "f8ab038609184e72a0008302710094cfe5e259e2c3558479db3aadbc1cb6e7c7c3454880b844a9059cbb00000000000000000000000039944247c2edf660d86d57764b58d83b8eee9014000000000000000000000000000000000000000000000000000000000000006426a0f4aa5630264f6c86dff7550d3c917c01ef665daa27c5f5f07d900bd2985e8436a01174a76a632936a17ff05195d335da4ed84e70d27ecc7c2662f310d46e255a90";
        raw_transfer_bpc.sender = "";
        auto && raw_transfer_bpc_data = bytes();
        raw_transfer_bpc.pack(raw_transfer_bpc_data);
        mocked_context raw_transfer_bpc_ctx("bpa"_n.value, "bpa"_n.value, "raw"_n.value, raw_transfer_bpc_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn11 = [&]() {
            backend.initialize(&raw_transfer_bpc_ctx);
            const auto& res = backend.call(
                    &raw_transfer_bpc_ctx, "env", "apply", raw_transfer_bpc_ctx.get_receiver(),
                    raw_transfer_bpc_ctx.get_account(),
                    raw_transfer_bpc_ctx.get_action());
        };
        backend.timed_run(wd, fn11);

//        // setcode action
//        struct setcode_type {
//            eth_addr eth_address;
//            hex_code evm_code;
//            void pack(vector<char>& dest) {
//                dest.emplace_back(eth_address.size());
//                copy(eth_address.begin(), eth_address.end(), back_inserter<vector<char> >(dest));
//                dest.emplace_back(evm_code.size());
//                copy(evm_code.begin(), evm_code.end(), back_inserter<vector<char> >(dest));
//            }
//        };
//        auto && setcode_act = setcode_type{};
//        setcode_act.eth_address = "d81f4358cb8cab53d005e7f47c7ba3f5116000a6";
//        setcode_act.evm_code = "6080604052600436106100ba576000357c0100000000000000000000000000000000000000000000000000000000900463ffffffff16806306fdde03146100bf578063095ea7b31461014f57806318160ddd146101b457806323b872dd146101df57806327e235e314610264578063313ce567146102bb5780635c658165146102ec57806370a082311461036357806395d89b41146103ba578063a9059cbb1461044a578063d74a99d4146104af578063dd62ed3e14610575575b600080fd5b3480156100cb57600080fd5b506100d46105ec565b6040518080602001828103825283818151815260200191508051906020019080838360005b838110156101145780820151818401526020810190506100f9565b50505050905090810190601f1680156101415780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b34801561015b57600080fd5b5061019a600480360381019080803573ffffffffffffffffffffffffffffffffffffffff1690602001909291908035906020019092919050505061068a565b604051808215151515815260200191505060405180910390f35b3480156101c057600080fd5b506101c961077c565b6040518082815260200191505060405180910390f35b3480156101eb57600080fd5b5061024a600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190803573ffffffffffffffffffffffffffffffffffffffff16906020019092919080359060200190929190505050610782565b604051808215151515815260200191505060405180910390f35b34801561027057600080fd5b506102a5600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190505050610a1c565b6040518082815260200191505060405180910390f35b3480156102c757600080fd5b506102d0610a34565b604051808260ff1660ff16815260200191505060405180910390f35b3480156102f857600080fd5b5061034d600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190803573ffffffffffffffffffffffffffffffffffffffff169060200190929190505050610a47565b6040518082815260200191505060405180910390f35b34801561036f57600080fd5b506103a4600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190505050610a6c565b6040518082815260200191505060405180910390f35b3480156103c657600080fd5b506103cf610ab5565b6040518080602001828103825283818151815260200191508051906020019080838360005b8381101561040f5780820151818401526020810190506103f4565b50505050905090810190601f16801561043c5780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b34801561045657600080fd5b50610495600480360381019080803573ffffffffffffffffffffffffffffffffffffffff16906020019092919080359060200190929190505050610b53565b604051808215151515815260200191505060405180910390f35b3480156104bb57600080fd5b5061057360048036038101908080359060200190929190803590602001908201803590602001908080601f0160208091040260200160405190810160405280939291908181526020018383808284378201915050505050509192919290803560ff169060200190929190803590602001908201803590602001908080601f0160208091040260200160405190810160405280939291908181526020018383808284378201915050505050509192919290505050610cac565b005b34801561058157600080fd5b506105d6600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190803573ffffffffffffffffffffffffffffffffffffffff169060200190929190505050610d46565b6040518082815260200191505060405180910390f35b60038054600181600116156101000203166002900480601f0160208091040260200160405190810160405280929190818152602001828054600181600116156101000203166002900480156106825780601f1061065757610100808354040283529160200191610682565b820191906000526020600020905b81548152906001019060200180831161066557829003601f168201915b505050505081565b600081600260003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925846040518082815260200191505060405180910390a36001905092915050565b60005481565b600080600260008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054905082600160008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054101580156108535750828110155b151561085e57600080fd5b82600160008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000206000828254019250508190555082600160008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825403925050819055507fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff8110156109ab5782600260008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825403925050819055505b8373ffffffffffffffffffffffffffffffffffffffff168573ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef856040518082815260200191505060405180910390a360019150509392505050565b60016020528060005260406000206000915090505481565b600460009054906101000a900460ff1681565b6002602052816000526040600020602052806000526040600020600091509150505481565b6000600160008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020549050919050565b60058054600181600116156101000203166002900480601f016020809104026020016040519081016040528092919081815260200182805460018160011615610100020316600290048015610b4b5780601f10610b2057610100808354040283529160200191610b4b565b820191906000526020600020905b815481529060010190602001808311610b2e57829003601f168201915b505050505081565b600081600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205410151515610ba357600080fd5b81600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000206000828254039250508190555081600160008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825401925050819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef846040518082815260200191505060405180910390a36001905092915050565b83600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002081905550836000819055508260039080519060200190610d0d929190610dcd565b5081600460006101000a81548160ff021916908360ff1602179055508060059080519060200190610d3f929190610dcd565b5050505050565b6000600260008473ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054905092915050565b828054600181600116156101000203166002900490600052602060002090601f016020900481019282601f10610e0e57805160ff1916838001178555610e3c565b82800160010185558215610e3c579182015b82811115610e3b578251825591602001919060010190610e20565b5b509050610e499190610e4d565b5090565b610e6f91905b80821115610e6b576000816000905550600101610e53565b5090565b905600a165627a7a72305820e55770e16d6fdfeef46f27fd89f7be39d403b35d937d11d065ff5e09a53062f30029";
//        auto && setcode_data = bytes();
//        setcode_act.pack(setcode_data);
//        mocked_context mc6("bpa"_n.value, "bpa"_n.value, "setcode"_n.value, setcode_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn6 = [&]() {
//            backend.initialize(&mc6);
//            const auto& res = backend.call(
//                    &mc6, "env", "apply", mc6.get_receiver(),
//                    mc6.get_account(),
//                    mc6.get_action());
//        };
//        backend.timed_run(wd, fn6);
//
//        // rawtrxexe action
//        struct rawtrxexe_type {
//            hex_code trx_param;
//            eth_addr eth_address;
//            eth_addr sender;
//            void pack(vector<char>& dest) {
//                dest.emplace_back(trx_param.size());
//                copy(trx_param.begin(), trx_param.end(), back_inserter<vector<char> >(dest));
//                dest.emplace_back(eth_address.size());
//                copy(eth_address.begin(), eth_address.end(), back_inserter<vector<char> >(dest));
//                dest.emplace_back(sender.size());
//                copy(sender.begin(), sender.end(), back_inserter<vector<char> >(dest));
//            }
//        };
//
//        //getTotalSupply  ethaddress
//        auto && rawtrxexe_act = rawtrxexe_type{};
//        rawtrxexe_act.trx_param = "18160ddd";
//        rawtrxexe_act.eth_address = "d81f4358cb8cab53d005e7f47c7ba3f5116000a6";
//        rawtrxexe_act.sender = "d81f4358cb8cab53d005e7f47c7ba3f5116000a6";
//        auto && rawtrxexe_data = bytes();
//        rawtrxexe_act.pack(rawtrxexe_data);
//        mocked_context mc7("bpa"_n.value, "bpa"_n.value, "rawtrxexe"_n.value, rawtrxexe_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn7 = [&]() {
//            backend.initialize(&mc7);
//            const auto& res = backend.call(
//                    &mc7, "env", "apply", mc7.get_receiver(),
//                    mc7.get_account(),
//                    mc7.get_action());
//        };
//        backend.timed_run(wd, fn7);
//
//        //hex create token
//        auto && rawtrxexe_act2 = rawtrxexe_type{};
//        rawtrxexe_act2.trx_param = "d74a99d400000000000000000000000000000000000000000000000000000000000027100000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000000000000000000000000000000000000000000a746f6b656e20746573740000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000035359530000000000000000000000000000000000000000000000000000000000";
//        rawtrxexe_act2.eth_address = "d81f4358cb8cab53d005e7f47c7ba3f5116000a6";
//        rawtrxexe_act2.sender = "";
//        auto && rawtrxexe_data2 = bytes();
//        rawtrxexe_act2.pack(rawtrxexe_data2);
//        mocked_context mc8("bpa"_n.value, "bpa"_n.value, "rawtrxexe"_n.value, rawtrxexe_data2, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn8 = [&]() {
//            backend.initialize(&mc8);
//            const auto& res = backend.call(
//                    &mc8, "env", "apply", mc8.get_receiver(),
//                    mc8.get_account(),
//                    mc8.get_action());
//        };
//        backend.timed_run(wd, fn8);
//
//        //transfer bpc 100
//        auto && rawtrxexe_act3 = rawtrxexe_type{};
//        rawtrxexe_act3.trx_param = "a9059cbb00000000000000000000000039944247c2edf660d86d57764b58d83b8eee90140000000000000000000000000000000000000000000000000000000000000064";
//        rawtrxexe_act3.eth_address = "d81f4358cb8cab53d005e7f47c7ba3f5116000a6";
//        rawtrxexe_act3.sender = "";
//        auto && rawtrxexe_data3 = bytes();
//        rawtrxexe_act3.pack(rawtrxexe_data3);
//        mocked_context mc88("bpa"_n.value, "bpa"_n.value, "rawtrxexe"_n.value, rawtrxexe_data3, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn88 = [&]() {
//            backend.initialize(&mc88);
//            const auto& res = backend.call(
//                    &mc88, "env", "apply", mc88.get_receiver(),
//                    mc88.get_account(),
//                    mc88.get_action());
//        };
//        backend.timed_run(wd, fn88);
//
//        //transfer bpd 500
//        auto && rawtrxexe_act4 = rawtrxexe_type{};
//        rawtrxexe_act4.trx_param = "a9059cbb000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d100000000000000000000000000000000000000000000000000000000000001f4";
//        rawtrxexe_act4.eth_address = "d81f4358cb8cab53d005e7f47c7ba3f5116000a6";
//        rawtrxexe_act4.sender = "";
//        auto && rawtrxexe_data4 = bytes();
//        rawtrxexe_act4.pack(rawtrxexe_data4);
//        mocked_context mc888("bpa"_n.value, "bpa"_n.value, "rawtrxexe"_n.value, rawtrxexe_data4, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn888 = [&]() {
//            backend.initialize(&mc888);
//            const auto& res = backend.call(
//                    &mc888, "env", "apply", mc888.get_receiver(),
//                    mc888.get_account(),
//                    mc888.get_action());
//        };
//        backend.timed_run(wd, fn888);
//
//        //approve .... bpd approve bpc spend 200
//        auto && rawtrxexe_act5 = rawtrxexe_type{};
//        rawtrxexe_act5.trx_param = "095ea7b3000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d100000000000000000000000000000000000000000000000000000000000000c8";
//        rawtrxexe_act5.eth_address = "d81f4358cb8cab53d005e7f47c7ba3f5116000a6";
//        rawtrxexe_act5.sender = "e327e755438fbdf9e60891d9b752da10a38514d1";
//        auto && rawtrxexe_data5 = bytes();
//        rawtrxexe_act5.pack(rawtrxexe_data5);
//        mocked_context mc8888("bpa"_n.value, "bpa"_n.value, "rawtrxexe"_n.value, rawtrxexe_data5, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn8888 = [&]() {
//            backend.initialize(&mc8888);
//            const auto& res = backend.call(
//                    &mc8888, "env", "apply", mc8888.get_receiver(),
//                    mc8888.get_account(),
//                    mc8888.get_action());
//        };
//        backend.timed_run(wd, fn8888);
//
//        //get allowance
//        auto && rawtrxexe_act6 = rawtrxexe_type{};
//        rawtrxexe_act6.trx_param = "dd62ed3e000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d1000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d1";
//        rawtrxexe_act6.eth_address = "d81f4358cb8cab53d005e7f47c7ba3f5116000a6";
//        rawtrxexe_act6.sender = "e327e755438fbdf9e60891d9b752da10a38514d1";
//        auto && rawtrxexe_data6 = bytes();
//        rawtrxexe_act6.pack(rawtrxexe_data6);
//        mocked_context mc88888("bpa"_n.value, "bpa"_n.value, "rawtrxexe"_n.value, rawtrxexe_data6, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn88888 = [&]() {
//            backend.initialize(&mc88888);
//            const auto& res = backend.call(
//                    &mc88888, "env", "apply", mc88888.get_receiver(),
//                    mc88888.get_account(),
//                    mc88888.get_action());
//        };
//        backend.timed_run(wd, fn88888);
//
//        //transfer from bpd to bpc 20
//        auto && rawtrxexe_act7 = rawtrxexe_type{};
//        rawtrxexe_act7.trx_param = "23b872dd000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d100000000000000000000000039944247c2edf660d86d57764b58d83b8eee90140000000000000000000000000000000000000000000000000000000000000014";
//        rawtrxexe_act7.eth_address = "d81f4358cb8cab53d005e7f47c7ba3f5116000a6";
//        rawtrxexe_act7.sender = "e327e755438fbdf9e60891d9b752da10a38514d1";
//        auto && rawtrxexe_data7 = bytes();
//        rawtrxexe_act7.pack(rawtrxexe_data6);
//        mocked_context mc888888("bpa"_n.value, "bpa"_n.value, "rawtrxexe"_n.value, rawtrxexe_data7, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn888888 = [&]() {
//            backend.initialize(&mc888888);
//            const auto& res = backend.call(
//                    &mc888888, "env", "apply", mc888888.get_receiver(),
//                    mc888888.get_account(),
//                    mc888888.get_action());
//        };
//        backend.timed_run(wd, fn888888);
//
//        // hexcodegen action
//        mocked_context mc9("bpa"_n.value, "bpa"_n.value, "hexcodegen"_n.value, bytes(), database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn9 = [&]() {
//            backend.initialize(&mc9);
//            const auto& res = backend.call(
//                    &mc9, "env", "apply", mc9.get_receiver(),
//                    mc9.get_account(),
//                    mc9.get_action());
//        };
//        backend.timed_run(wd, fn9);
//
        // create token

//
//        // get balance bpb
//        auto && raw_act1 = raw_type{};
//        raw_act1.trx_code = "f88a038609184e72a0008302710094d81f4358cb8cab53d005e7f47c7ba3f5116000a680a470a08231000000000000000000000000d81f4358cb8cab53d005e7f47c7ba3f5116000a626a064dc22afc3d6ccef9a04c4d5c61c5bcb915e1534f1e94ca8a573014e52cc1bf4a0725033f016d6e06a94372c1b6e0b227c502065197ece3907cd5f2e48f03bd7fc";
//        raw_act1.sender = "";
//        auto && raw_data1 = bytes();
//        raw_act1.pack(raw_data1);
//        mocked_context mc1010("bpa"_n.value, "bpa"_n.value, "raw"_n.value, raw_data1, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn1010 = [&]() {
//            backend.initialize(&mc1010);
//            const auto& res = backend.call(
//                    &mc1010, "env", "apply", mc1010.get_receiver(),
//                    mc1010.get_account(),
//                    mc1010.get_action());
//        };
//        backend.timed_run(wd, fn1010);
//

//
//        // transfer bpd 500
//        auto && raw_act3 = raw_type{};
//        raw_act3.trx_code = "f8ab038609184e72a0008302710094d81f4358cb8cab53d005e7f47c7ba3f5116000a680b844a9059cbb00000000000000000000000039944247c2edf660d86d57764b58d83b8eee9014000000000000000000000000000000000000000000000000000000000000006426a002a8f35c445314e91c44b0d6a37de65514315ca71a6367da114705791e93d2d3a02224b1c800f71726930b62d3f17e06b4a1d28767d7a742ee686cf124ea6939ae";
//        raw_act3.sender = "";
//        auto && raw_data3 = bytes();
//        raw_act3.pack(raw_data3);
//        mocked_context mc10101010("bpa"_n.value, "bpa"_n.value, "raw"_n.value, raw_data3, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn10101010 = [&]() {
//            backend.initialize(&mc10101010);
//            const auto& res = backend.call(
//                    &mc10101010, "env", "apply", mc10101010.get_receiver(),
//                    mc10101010.get_account(),
//                    mc10101010.get_action());
//        };
//        backend.timed_run(wd, fn10101010);
//
//
//        // balance of bpc
//        auto && raw_act4 = raw_type{};
//        raw_act4.trx_code = "f88a018609184e72a0008302710094d81f4358cb8cab53d005e7f47c7ba3f5116000a680a470a0823100000000000000000000000039944247c2edf660d86d57764b58d83b8eee901425a08b3b346543efb20ad53b97a897871061c7d1503597a3efbf382691491858e06da03d7282ebbcc85c97d6e3f9022e235b2fb5c480e77fb2ac400e49063be9dfb5c6";
//        raw_act4.sender = "";
//        auto && raw_data4 = bytes();
//        raw_act4.pack(raw_data4);
//        mocked_context mc1010101010("bpa"_n.value, "bpa"_n.value, "raw"_n.value, raw_data4, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn1010101010 = [&]() {
//            backend.initialize(&mc1010101010);
//            const auto& res = backend.call(
//                    &mc1010101010, "env", "apply", mc1010101010.get_receiver(),
//                    mc1010101010.get_account(),
//                    mc1010101010.get_action());
//        };
//        backend.timed_run(wd, fn1010101010);
//
//
//        // balance of bpd
//        auto && raw_act5 = raw_type{};
//        raw_act5.trx_code = "f88a018609184e72a0008302710094d81f4358cb8cab53d005e7f47c7ba3f5116000a680a470a0823100000000000000000000000039944247c2edf660d86d57764b58d83b8eee901425a08b3b346543efb20ad53b97a897871061c7d1503597a3efbf382691491858e06da03d7282ebbcc85c97d6e3f9022e235b2fb5c480e77fb2ac400e49063be9dfb5c6";
//        raw_act5.sender = "";
//        auto && raw_data5 = bytes();
//        raw_act5.pack(raw_data5);
//        mocked_context mc101010101010("bpa"_n.value, "bpa"_n.value, "raw"_n.value, raw_data5, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn101010101010 = [&]() {
//            backend.initialize(&mc101010101010);
//            const auto& res = backend.call(
//                    &mc101010101010, "env", "apply", mc101010101010.get_receiver(),
//                    mc101010101010.get_account(),
//                    mc101010101010.get_action());
//        };
//        backend.timed_run(wd, fn101010101010);
//
//        // bpd approve bpc spend 200
//        auto && raw_act6 = raw_type{};
//        raw_act6.trx_code = "f8ab038609184e72a0008302710094d81f4358cb8cab53d005e7f47c7ba3f5116000a680b844095ea7b3000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d100000000000000000000000000000000000000000000000000000000000000c825a0f01586388d98b925f34bb01a1b887d31d14a9388c6e847829f5294238a2b1d35a03f14a9c84d32a8314f0f55bc6038b4b6a9612a8ab19dfe43ec9e73cd5ed4ecfa";
//        raw_act6.sender = "";
//        auto && raw_data6 = bytes();
//        raw_act6.pack(raw_data6);
//        mocked_context mc10101010101010("bpa"_n.value, "bpa"_n.value, "raw"_n.value, raw_data6, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn10101010101010 = [&]() {
//            backend.initialize(&mc10101010101010);
//            const auto& res = backend.call(
//                    &mc10101010101010, "env", "apply", mc10101010101010.get_receiver(),
//                    mc10101010101010.get_account(),
//                    mc10101010101010.get_action());
//        };
//        backend.timed_run(wd, fn10101010101010);
//
//        // get allowance
//        auto && raw_act7 = raw_type{};
//        raw_act7.trx_code = "f8ab038609184e72a0008302710094d81f4358cb8cab53d005e7f47c7ba3f5116000a680b844dd62ed3e000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d1000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d125a0899510e04af46df3119a8b4f02c9b86e4a67de104c946243a5b6f3de1af06315a05709b94d442511016c7825ce9dbb1162422d7eb06d379eddc87fcdb816e0cd21";
//        raw_act7.sender = "";
//        auto && raw_data7 = bytes();
//        raw_act7.pack(raw_data7);
//        mocked_context mc1010101010101010("bpa"_n.value, "bpa"_n.value, "raw"_n.value, raw_data7, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn1010101010101010 = [&]() {
//            backend.initialize(&mc1010101010101010);
//            const auto& res = backend.call(
//                    &mc1010101010101010, "env", "apply", mc1010101010101010.get_receiver(),
//                    mc1010101010101010.get_account(),
//                    mc1010101010101010.get_action());
//        };
//        backend.timed_run(wd, fn1010101010101010);
//
//
//        // transfer from
//        auto && raw_act8 = raw_type{};
//        raw_act8.trx_code = "f8ab038609184e72a0008302710094d81f4358cb8cab53d005e7f47c7ba3f5116000a680b844dd62ed3e000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d1000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d125a0899510e04af46df3119a8b4f02c9b86e4a67de104c946243a5b6f3de1af06315a05709b94d442511016c7825ce9dbb1162422d7eb06d379eddc87fcdb816e0cd21";
//        raw_act8.sender = "";
//        auto && raw_data8 = bytes();
//        raw_act8.pack(raw_data8);
//        mocked_context mc101010101010101010("bpa"_n.value, "bpa"_n.value, "raw"_n.value, raw_data8, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn101010101010101010 = [&]() {
//            backend.initialize(&mc101010101010101010);
//            const auto& res = backend.call(
//                    &mc101010101010101010, "env", "apply", mc101010101010101010.get_receiver(),
//                    mc101010101010101010.get_account(),
//                    mc101010101010101010.get_action());
//        };
//        backend.timed_run(wd, fn101010101010101010);
//
//
//        // rawtest action
//        struct rawtest_type {
//            hex_code hexcode;
//            void pack(vector<char>& dest) {
//                dest.emplace_back(hexcode.size());
//                copy(hexcode.begin(), hexcode.end(), back_inserter<vector<char> >(dest));
//            }
//        };
//        auto && rawtest_act = rawtest_type{};
//        rawtest_act.hexcode = "d74a99d400000000000000000000000000000000000000000000000000000000000027100000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000000000000000000000000000000000000000000a746f6b656e20746573740000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000035359530000000000000000000000000000000000000000000000000000000000";
//        auto && rawtest_data = bytes();
//        rawtest_act.pack(rawtest_data);
//        mocked_context mc11("bpa"_n.value, "bpa"_n.value, "rawtest"_n.value, rawtest_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn11 = [&]() {
//            backend.initialize(&mc11);
//            const auto& res = backend.call(
//                    &mc11, "env", "apply", mc11.get_receiver(),
//                    mc11.get_account(),
//                    mc11.get_action());
//        };
//        backend.timed_run(wd, fn11);
//
//        struct asset {
//            uint64_t amount;
//            uint64_t sym;
//        };
//
//
//        // verifysig action
//        struct verifysig_type {
//            hex_code trx_code;
//            void pack(vector<char>& dest) {
//                dest.emplace_back(trx_code.size());
//                copy(trx_code.begin(), trx_code.end(), back_inserter<vector<char> >(dest));
//            }
//        };
//        auto && verifysig_act = verifysig_type{};
//        verifysig_act.trx_code = "d74a99d400000000000000000000000000000000000000000000000000000000000027100000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000000000000000000000000000000000000000000a746f6b656e20746573740000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000035359530000000000000000000000000000000000000000000000000000000000";
//        auto && verifysig_data = bytes();
//        verifysig_act.pack(verifysig_data);
//        mocked_context mc12("bpa"_n.value, "bpa"_n.value, "verifysig"_n.value, verifysig_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn12 = [&]() {
//            backend.initialize(&mc12);
//            const auto& res = backend.call(
//                    &mc12, "env", "apply", mc12.get_receiver(),
//                    mc12.get_account(),
//                    mc12.get_action());
//        };
//        backend.timed_run(wd, fn12);
//
//        // withdraw action
//        struct withdraw_type {
//            name  eos_account;
//            asset amount;
//        };
//        auto && withdraw_act = withdraw_type{};
//        withdraw_act.eos_account = "bpc"_n.value;
//        withdraw_act.amount = {10000, 1397703938};
//        auto && withdraw_data = bytes();
//        withdraw_data.resize(sizeof(withdraw_act));
//        memcpy(&withdraw_data[0], &withdraw_act, sizeof(withdraw_act));
//        mocked_context mc13("bpa"_n.value, "bpa"_n.value, "transfers"_n.value, withdraw_data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
//        auto fn13 = [&]() {
//            backend.initialize(&mc13);
//            const auto& res = backend.call(
//                    &mc13, "env", "apply", mc13.get_receiver(),
//                    mc13.get_account(),
//                    mc13.get_action());
//        };
//        backend.timed_run(wd, fn11);

    };
};