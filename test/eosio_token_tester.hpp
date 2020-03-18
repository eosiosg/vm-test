//
// Created by Vince on 26/2/20.
//
#include <stdio.h>
#include <eosio/vm/backend.hpp>
#include <eosio/vm/watchdog.hpp>
#include <eosio/vm/execution_context.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include "name.hpp"
#include "mocked_context.hpp"

class eosio_token_tester : public testing::Test {
protected:
  void execute_contract(const std::string &path) {
      using backend_t = eosio::vm::backend<mocked_context>;
      using rhf_t = eosio::vm::registered_host_functions<mocked_context>;
    std::ifstream input(path, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = input.tellg();
    std::vector<char> tmp(pos);
    input.seekg(0, std::ios::beg);
    input.read(&tmp[0], pos);

    std::vector<uint8_t> wasm;

    std::copy(tmp.begin(), tmp.end(), std::back_inserter(wasm));

      backend_t backend(wasm);
      eosio::vm::wasm_allocator wa;
//      eosio::vm::watchdog wd{std::chrono::seconds(3)};
      // Point the backend to the allocator you want it to use.
      backend.set_wasm_allocator(&wa);
      backend.initialize();
      // Resolve the host functions indices.

      // Instantiate a "host"

      db_type database;
      secondary_key_type<uint64_t > i64_index;
      secondary_key_type<array<uint128_t, 2>> i256_index;
      typedef struct __attribute__((packed)) {
        int64_t amount;
        uint64_t symbol;
    } asset;
      struct issue {
        uint64_t issuer;
        asset    token;
        string   memo;
        void pack(vector<char>& dest) {
            dest.resize(sizeof(issuer ) + sizeof(token));
            memcpy(&dest[0], &issuer , sizeof(issuer ));
            memcpy(&dest[sizeof(issuer )], &token , sizeof(token ));
            dest.emplace_back(memo.size());
            copy(memo.begin(), memo.end(), back_inserter<vector<char> >(dest));
        }
    };
      auto issue_s = issue{3773036822876127232, 500000, 1313559555, "aaaaaa"};


    auto && data = bytes();
    issue_s.pack(data);


    mocked_context hm(".bob"_n.value, ".bob"_n.value, "create"_n.value, data, database, i64_index, i256_index);

    rhf_t::template add<mocked_context, &mocked_context::require_auth, eosio::vm::wasm_allocator>("env", "require_auth");
    rhf_t::template add<mocked_context, &mocked_context::eosio_assert, eosio::vm::wasm_allocator>("env", "eosio_assert");
    rhf_t::template add<mocked_context, &mocked_context::db_find_i64, eosio::vm::wasm_allocator>("env", "db_find_i64");
    rhf_t::template add<mocked_context, &mocked_context::current_receiver, eosio::vm::wasm_allocator>("env", "current_receiver");
    rhf_t::template add<mocked_context, &mocked_context::abort, eosio::vm::wasm_allocator>("env", "abort");
    rhf_t::template add<mocked_context, &mocked_context::memset, eosio::vm::wasm_allocator>("env", "memset");
    rhf_t::template add<mocked_context, &mocked_context::db_store_i64, eosio::vm::wasm_allocator>("env", "db_store_i64");
    rhf_t::template add<mocked_context, &mocked_context::db_update_i64, eosio::vm::wasm_allocator>("env", "db_update_i64");
    rhf_t::template add<mocked_context, &mocked_context::memcpy, eosio::vm::wasm_allocator>("env", "memcpy");
    rhf_t::template add<mocked_context, &mocked_context::is_account, eosio::vm::wasm_allocator>("env", "is_account");
    rhf_t::template add<mocked_context, &mocked_context::require_recipient, eosio::vm::wasm_allocator>("env", "require_recipient");
    rhf_t::template add<mocked_context, &mocked_context::has_auth, eosio::vm::wasm_allocator>("env", "has_auth");
    rhf_t::template add<mocked_context, &mocked_context::db_next_i64, eosio::vm::wasm_allocator>("env", "db_next_i64");
    rhf_t::template add<mocked_context, &mocked_context::action_data_size, eosio::vm::wasm_allocator>("env", "action_data_size");
    rhf_t::template add<mocked_context, &mocked_context::read_action_data, eosio::vm::wasm_allocator>("env", "read_action_data");
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
    rhf_t::template add<mocked_context, &mocked_context::eosio_assert_code, eosio::vm::wasm_allocator>("env", "eosio_assert_code");
    rhf_t::template add<mocked_context, &mocked_context::db_get_i64, eosio::vm::wasm_allocator>("env", "db_get_i64");
    rhf_t::template add<mocked_context, &mocked_context::db_remove_i64, eosio::vm::wasm_allocator>("env", "db_remove_i64");

    rhf_t::resolve(backend.get_module());

    backend.call(&hm, "env", "apply",".bob"_n.value, ".bob"_n.value, "create"_n.value);

  }
};