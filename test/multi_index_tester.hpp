//
// Created by Vince on 8/3/20.
//
#include <eosio/vm/backend.hpp>
#include <eosio/vm/watchdog.hpp>
#include <eosio/vm/execution_context.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include "../lib/name.hpp"
#include "../lib/mocked_context.hpp"

using backend_t = eosio::vm::backend<mocked_context>;
using rhf_t = eosio::vm::registered_host_functions<mocked_context>;

class multi_index_tester : public testing::Test {
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
        eosio::vm::watchdog wd{std::chrono::seconds(300000)};
        // Point the backend to the allocator you want it to use.
        backend.set_wasm_allocator(&wa);

        // Resolve the host functions indices.

        // Instantiate a "host"

        db_type database;
        secondary_key_type<uint64_t> i64_index;
        secondary_key_type<array<uint128_t, 2>> i256_index;

        vector<kv_type> keyval_cache{};
        vector<i64_sec_kv_type> i64_sec_keyval_cache{};
        vector<i256_sec_kv_type> i256_sec_keyval_cache{};

        struct set {
            uint64_t user;
        };

        struct bysec {
            uint64_t secid;
        };

        struct mod {
            uint64_t user;
            uint32_t n;

            void pack(vector<char>& dest) {
                dest.resize(sizeof(user ) + sizeof(n));
                memcpy(&dest[0], &user , sizeof(user ));
                memcpy(&dest[sizeof(user )], &n , sizeof(n ));
//                auto nd = n;
//                do {
//                    uint8_t b = uint8_t(nd) & 0x7f;
//                    nd >>= 7;
//                    b |= ((nd > 0) << 7);
//                    dest.emplace_back(b);
//                } while ( nd );
            }
        };

        auto && set_1 = set{"bob"_n.value};
        auto && set_2 = set{"alice"_n.value};
        auto && mod_1 = mod{"bob"_n.value, 10};
        auto && mod_2 = mod{"alice"_n.value, 20};
        auto && bysec_s = bysec{"bob"_n.value};


        rhf_t::template add<mocked_context, &mocked_context::eosio_assert, eosio::vm::wasm_allocator>("env", "eosio_assert");
        rhf_t::template add<mocked_context, &mocked_context::db_find_i64, eosio::vm::wasm_allocator>("env", "db_find_i64");
        rhf_t::template add<mocked_context, &mocked_context::current_receiver, eosio::vm::wasm_allocator>("env", "current_receiver");
        rhf_t::template add<mocked_context, &mocked_context::abort, eosio::vm::wasm_allocator>("env", "abort");
        rhf_t::template add<mocked_context, &mocked_context::memset, eosio::vm::wasm_allocator>("env", "memset");
        rhf_t::template add<mocked_context, &mocked_context::db_store_i64, eosio::vm::wasm_allocator>("env", "db_store_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_store, eosio::vm::wasm_allocator>("env", "db_idx64_store");
        rhf_t::template add<mocked_context, &mocked_context::prints_l, eosio::vm::wasm_allocator>("env", "prints_l");
        rhf_t::template add<mocked_context, &mocked_context::printn, eosio::vm::wasm_allocator>("env", "printn");
        rhf_t::template add<mocked_context, &mocked_context::printui, eosio::vm::wasm_allocator>("env", "printui");
        rhf_t::template add<mocked_context, &mocked_context::prints, eosio::vm::wasm_allocator>("env", "prints");
        rhf_t::template add<mocked_context, &mocked_context::db_next_i64, eosio::vm::wasm_allocator>("env", "db_next_i64");
        rhf_t::template add<mocked_context, &mocked_context::action_data_size, eosio::vm::wasm_allocator>("env", "action_data_size");
        rhf_t::template add<mocked_context, &mocked_context::read_action_data, eosio::vm::wasm_allocator>("env", "read_action_data");
        rhf_t::template add<mocked_context, &mocked_context::memcpy, eosio::vm::wasm_allocator>("env", "memcpy");
        rhf_t::template add<mocked_context, &mocked_context::eosio_assert_code, eosio::vm::wasm_allocator>("env", "eosio_assert_code");
        rhf_t::template add<mocked_context, &mocked_context::db_get_i64, eosio::vm::wasm_allocator>("env", "db_get_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_lowerbound, eosio::vm::wasm_allocator>("env", "db_idx64_lowerbound");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_find_primary, eosio::vm::wasm_allocator>("env", "db_idx64_find_primary");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_next, eosio::vm::wasm_allocator>("env", "db_idx64_next");
        rhf_t::template add<mocked_context, &mocked_context::db_update_i64, eosio::vm::wasm_allocator>("env", "db_update_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_update, eosio::vm::wasm_allocator>("env", "db_idx64_update");
        rhf_t::template add<mocked_context, &mocked_context::db_remove_i64, eosio::vm::wasm_allocator>("env", "db_remove_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_remove, eosio::vm::wasm_allocator>("env", "db_idx64_remove");

        rhf_t::resolve(backend.get_module());


        auto size = sizeof(set_1 );
        auto && data = bytes();
        data.resize(size);
        memcpy(&data[0], &set_1 , size);
        mocked_context mc1(".bob"_n.value, ".bob"_n.value, "set"_n.value, data, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn1 = [&]() {
            backend.initialize(&mc1);
            const auto& res = backend.call(
                    &mc1, "env", "apply", mc1.get_receiver(),
                    mc1.get_account(),
                    mc1.get_action());
        };
        backend.timed_run(wd, fn1);
        database.print_all();
        i64_index.print_all();
        cout << endl;

        auto size1 = sizeof(set_2 );
        auto && data1 = bytes();
        data1.resize(size1);
        memcpy(&data1[0], &set_2 , size1);
        mocked_context mc2(".bob"_n.value, ".bob"_n.value, "set"_n.value, data1, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn2 = [&]() {
            backend.initialize(&mc2);
            const auto& res = backend.call(
                    &mc2, "env", "apply", mc2.get_receiver(),
                    mc2.get_account(),
                    mc2.get_action());
        };
        backend.timed_run(wd, fn2);
        database.print_all();
        i64_index.print_all();
        cout << endl;

        auto && data2 = bytes();
        mod_1.pack(data2);
        mocked_context mc3(".bob"_n.value, ".bob"_n.value, "mod"_n.value, data2, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn3 = [&]() {
            backend.initialize(&mc3);
            const auto& res = backend.call(
                    &mc3, "env", "apply", mc3.get_receiver(),
                    mc3.get_account(),
                    mc3.get_action());
        };
        backend.timed_run(wd, fn3);
        database.print_all();
        i64_index.print_all();
        cout << endl;


        auto && data3 = bytes();
        mod_2.pack(data3);
        mocked_context mc4(".bob"_n.value, ".bob"_n.value, "mod"_n.value, data3, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn4 = [&]() {
            backend.initialize(&mc4);
            const auto& res = backend.call(
                    &mc4, "env", "apply", mc4.get_receiver(),
                    mc4.get_account(),
                    mc4.get_action());
        };
        backend.timed_run(wd, fn4);
        database.print_all();
        i64_index.print_all();
        cout << endl;


        auto size4 = sizeof(bysec_s );
        auto && data4 = bytes();
        data4.resize(size4);
        memcpy(&data4[0], &bysec_s , size4);
        mocked_context mc5(".bob"_n.value, ".bob"_n.value, "bysec"_n.value, data4, database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn5 = [&]() {
            backend.initialize(&mc5);
            const auto& res = backend.call(
                    &mc5, "env", "apply", mc5.get_receiver(),
                    mc5.get_account(),
                    mc5.get_action());
        };
        backend.timed_run(wd, fn5);
        database.print_all();
        i64_index.print_all();
    }
};