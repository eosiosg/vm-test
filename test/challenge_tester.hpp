//
// Created by Vince on 2/3/20.
//

#include <eosio/vm/backend.hpp>
#include <memory>
#include <utility>
#include <eosio/vm/watchdog.hpp>
#include <eosio/vm/execution_context.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include "name.hpp"
#include "mocked_context.hpp"
#include <openssl/sha.h>

typedef string eth_addr;
typedef string hex_code;
typedef string sha256_type;
typedef uint64_t name;



using backend_t = eosio::vm::backend<mocked_context>;
using rhf_t = eosio::vm::registered_host_functions<mocked_context>;

void pack_string(string& str, vector<char>& dest) {
    auto size = str.size();
    uint64_t val = size;
    do {
        uint8_t b = uint8_t(val) & 0x7f;
        val >>= 7;
        b |= ((val > 0) << 7);
        dest.emplace_back(b);
    }while( val );
    copy(str.begin(), str.end(), back_inserter<vector<char> >(dest));
}
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

struct create_act {
    uint64_t eos_account;
    string   salt;
    void pack(vector<char>& dest) {
        dest.resize(sizeof(eos_account));
        memcpy(&dest[0], &eos_account , sizeof(eos_account ));
        pack_string(salt, dest);
    }
};

struct createeth_act {
    name        eos_account;
    sha256_type eth_address;
    void pack(vector<char>& dest) {
        dest.resize(sizeof(eos_account));
        memcpy(&dest[0], &eos_account , sizeof(eos_account ));
        pack_string(eth_address, dest);
    }
};

struct raw_act {
    hex_code trx_code;
    eth_addr sender;
    void pack(vector<char>& dest) {
        pack_string(trx_code, dest);
        dest.resize(dest.size()+20);
    }
};

struct rawtrxexe_act {
    hex_code trx_param;
    eth_addr eth_address;
    eth_addr sender;
    void pack(vector<char>& dest) {
        pack_string(trx_param, dest);
        pack_string(eth_address, dest);
        pack_string(sender, dest);
    }
};

class challenge_tester : public testing::Test {
public:
    void init(const std::string &path, uint64_t account) {

        std::ifstream input(path, std::ios::binary | std::ios::ate);
        std::ifstream::pos_type pos = input.tellg();
        std::vector<char> tmp(pos);
        input.seekg(0, std::ios::beg);
        input.read(&tmp[0], pos);
        std::vector<uint8_t> wasm;

        std::copy(tmp.begin(), tmp.end(), std::back_inserter(wasm));

        backend = std::make_shared<backend_t>(wasm);

        eosio::vm::wasm_allocator wa;
        // Point the backend to the allocator you want it to use.
        backend->set_wasm_allocator(&wa);
        // Resolve the host functions indices.
        keyval_cache = {};
        i64_sec_keyval_cache = {};
        i256_sec_keyval_cache = {};

        rhf_t::template add<mocked_context, &mocked_context::abort, eosio::vm::wasm_allocator>("env", "abort");
        rhf_t::template add<mocked_context, &mocked_context::eosio_assert, eosio::vm::wasm_allocator>("env",
                                                                                                      "eosio_assert");
        rhf_t::template add<mocked_context, &mocked_context::memset, eosio::vm::wasm_allocator>("env", "memset");
        rhf_t::template add<mocked_context, &mocked_context::memcpy, eosio::vm::wasm_allocator>("env", "memcpy");
        rhf_t::template add<mocked_context, &mocked_context::memmove, eosio::vm::wasm_allocator>("env", "memmove");
        rhf_t::template add<mocked_context, &mocked_context::__extendsftf2, eosio::vm::wasm_allocator>("env",
                                                                                                       "__extendsftf2");
        rhf_t::template add<mocked_context, &mocked_context::__floatsitf, eosio::vm::wasm_allocator>("env",
                                                                                                     "__floatsitf");
        rhf_t::template add<mocked_context, &mocked_context::__multf3, eosio::vm::wasm_allocator>("env", "__multf3");
        rhf_t::template add<mocked_context, &mocked_context::__floatunsitf, eosio::vm::wasm_allocator>("env",
                                                                                                       "__floatunsitf");
        rhf_t::template add<mocked_context, &mocked_context::__divtf3, eosio::vm::wasm_allocator>("env", "__divtf3");
        rhf_t::template add<mocked_context, &mocked_context::__addtf3, eosio::vm::wasm_allocator>("env", "__addtf3");
        rhf_t::template add<mocked_context, &mocked_context::__extenddftf2, eosio::vm::wasm_allocator>("env",
                                                                                                       "__extenddftf2");
        rhf_t::template add<mocked_context, &mocked_context::__eqtf2, eosio::vm::wasm_allocator>("env", "__eqtf2");
        rhf_t::template add<mocked_context, &mocked_context::__letf2, eosio::vm::wasm_allocator>("env", "__letf2");
        rhf_t::template add<mocked_context, &mocked_context::__netf2, eosio::vm::wasm_allocator>("env", "__netf2");
        rhf_t::template add<mocked_context, &mocked_context::__subtf3, eosio::vm::wasm_allocator>("env", "__subtf3");
        rhf_t::template add<mocked_context, &mocked_context::__trunctfdf2, eosio::vm::wasm_allocator>("env",
                                                                                                      "__trunctfdf2");
        rhf_t::template add<mocked_context, &mocked_context::__getf2, eosio::vm::wasm_allocator>("env", "__getf2");
        rhf_t::template add<mocked_context, &mocked_context::__trunctfsf2, eosio::vm::wasm_allocator>("env",
                                                                                                      "__trunctfsf2");
        rhf_t::template add<mocked_context, &mocked_context::prints_l, eosio::vm::wasm_allocator>("env", "prints_l");
        rhf_t::template add<mocked_context, &mocked_context::__unordtf2, eosio::vm::wasm_allocator>("env",
                                                                                                    "__unordtf2");
        rhf_t::template add<mocked_context, &mocked_context::__fixunstfsi, eosio::vm::wasm_allocator>("env",
                                                                                                      "__fixunstfsi");
        rhf_t::template add<mocked_context, &mocked_context::__fixtfsi, eosio::vm::wasm_allocator>("env", "__fixtfsi");
        rhf_t::template add<mocked_context, &mocked_context::__ashlti3, eosio::vm::wasm_allocator>("env", "__ashlti3");
        rhf_t::template add<mocked_context, &mocked_context::require_auth, eosio::vm::wasm_allocator>("env",
                                                                                                      "require_auth");
        rhf_t::template add<mocked_context, &mocked_context::db_lowerbound_i64, eosio::vm::wasm_allocator>("env",
                                                                                                           "db_lowerbound_i64");
        rhf_t::template add<mocked_context, &mocked_context::current_receiver, eosio::vm::wasm_allocator>("env",
                                                                                                          "current_receiver");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_lowerbound, eosio::vm::wasm_allocator>("env",
                                                                                                              "db_idx256_lowerbound");
        rhf_t::template add<mocked_context, &mocked_context::db_find_i64, eosio::vm::wasm_allocator>("env",
                                                                                                     "db_find_i64");
        rhf_t::template add<mocked_context, &mocked_context::assert_sha256, eosio::vm::wasm_allocator>("env",
                                                                                                       "assert_sha256");
        rhf_t::template add<mocked_context, &mocked_context::assert_sha1, eosio::vm::wasm_allocator>("env",
                                                                                                     "assert_sha1");
        rhf_t::template add<mocked_context, &mocked_context::assert_sha512, eosio::vm::wasm_allocator>("env",
                                                                                                       "assert_sha512");
        rhf_t::template add<mocked_context, &mocked_context::assert_ripemd160, eosio::vm::wasm_allocator>("env",
                                                                                                          "assert_ripemd160");
        rhf_t::template add<mocked_context, &mocked_context::sha256, eosio::vm::wasm_allocator>("env", "sha256");
        rhf_t::template add<mocked_context, &mocked_context::sha1, eosio::vm::wasm_allocator>("env", "sha1");
        rhf_t::template add<mocked_context, &mocked_context::sha512, eosio::vm::wasm_allocator>("env", "sha512");
        rhf_t::template add<mocked_context, &mocked_context::ripemd160, eosio::vm::wasm_allocator>("env", "ripemd160");
        rhf_t::template add<mocked_context, &mocked_context::recover_key, eosio::vm::wasm_allocator>("env",
                                                                                                     "recover_key");
        rhf_t::template add<mocked_context, &mocked_context::set_blockchain_parameters_packed, eosio::vm::wasm_allocator>(
                "env", "set_blockchain_parameters_packed");
        rhf_t::template add<mocked_context, &mocked_context::get_blockchain_parameters_packed, eosio::vm::wasm_allocator>(
                "env", "get_blockchain_parameters_packed");
        rhf_t::template add<mocked_context, &mocked_context::set_proposed_producers, eosio::vm::wasm_allocator>("env",
                                                                                                                "set_proposed_producers");
        rhf_t::template add<mocked_context, &mocked_context::current_time, eosio::vm::wasm_allocator>("env",
                                                                                                      "current_time");
        rhf_t::template add<mocked_context, &mocked_context::get_active_producers, eosio::vm::wasm_allocator>("env",
                                                                                                              "get_active_producers");
        rhf_t::template add<mocked_context, &mocked_context::assert_recover_key, eosio::vm::wasm_allocator>("env",
                                                                                                            "assert_recover_key");
        rhf_t::template add<mocked_context, &mocked_context::prints, eosio::vm::wasm_allocator>("env", "prints");
        rhf_t::template add<mocked_context, &mocked_context::printhex, eosio::vm::wasm_allocator>("env", "printhex");
        rhf_t::template add<mocked_context, &mocked_context::printui, eosio::vm::wasm_allocator>("env", "printui");
        rhf_t::template add<mocked_context, &mocked_context::db_store_i64, eosio::vm::wasm_allocator>("env",
                                                                                                      "db_store_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_update_i64, eosio::vm::wasm_allocator>("env",
                                                                                                       "db_update_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_find_primary, eosio::vm::wasm_allocator>("env",
                                                                                                                "db_idx256_find_primary");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_update, eosio::vm::wasm_allocator>("env",
                                                                                                          "db_idx256_update");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_find_primary, eosio::vm::wasm_allocator>("env",
                                                                                                               "db_idx64_find_primary");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_update, eosio::vm::wasm_allocator>("env",
                                                                                                         "db_idx64_update");
        rhf_t::template add<mocked_context, &mocked_context::send_inline, eosio::vm::wasm_allocator>("env",
                                                                                                     "send_inline");
        rhf_t::template add<mocked_context, &mocked_context::printi, eosio::vm::wasm_allocator>("env", "printi");
        rhf_t::template add<mocked_context, &mocked_context::action_data_size, eosio::vm::wasm_allocator>("env",
                                                                                                          "action_data_size");
        rhf_t::template add<mocked_context, &mocked_context::read_action_data, eosio::vm::wasm_allocator>("env",
                                                                                                          "read_action_data");
        rhf_t::template add<mocked_context, &mocked_context::eosio_assert_code, eosio::vm::wasm_allocator>("env",
                                                                                                           "eosio_assert_code");
        rhf_t::template add<mocked_context, &mocked_context::tapos_block_num, eosio::vm::wasm_allocator>("env",
                                                                                                         "tapos_block_num");
        rhf_t::template add<mocked_context, &mocked_context::db_get_i64, eosio::vm::wasm_allocator>("env",
                                                                                                    "db_get_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_store, eosio::vm::wasm_allocator>("env",
                                                                                                         "db_idx256_store");
        rhf_t::template add<mocked_context, &mocked_context::db_previous_i64, eosio::vm::wasm_allocator>("env",
                                                                                                         "db_previous_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_end_i64, eosio::vm::wasm_allocator>("env",
                                                                                                    "db_end_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_next, eosio::vm::wasm_allocator>("env",
                                                                                                        "db_idx256_next");
        rhf_t::template add<mocked_context, &mocked_context::db_remove_i64, eosio::vm::wasm_allocator>("env",
                                                                                                       "db_remove_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_remove, eosio::vm::wasm_allocator>("env",
                                                                                                          "db_idx256_remove");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_remove, eosio::vm::wasm_allocator>("env",
                                                                                                         "db_idx64_remove");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_store, eosio::vm::wasm_allocator>("env",
                                                                                                        "db_idx64_store");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_lowerbound, eosio::vm::wasm_allocator>("env",
                                                                                                             "db_idx64_lowerbound");
        rhf_t::template add<mocked_context, &mocked_context::__multi3, eosio::vm::wasm_allocator>("env", "__multi3");

        rhf_t::resolve(backend->get_module());
    };

    void set_token(extended_symbol ex_sym) {
        auto &&set_token = settoken_act{ex_sym.sym, ex_sym.contract};

        auto &&set_token_data = bytes();
        set_token.pack(set_token_data);
        mocked_context set_token_ctx(code, code, "settoken"_n.value, set_token_data, database,
                                     i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn1 = [&]() {
            backend->initialize(&set_token_ctx);
            const auto &res = backend->call(
                    &set_token_ctx, "env", "apply", set_token_ctx.get_receiver(),
                    set_token_ctx.get_account(),
                    set_token_ctx.get_action());
        };
        backend->timed_run(wd, fn1);
    }

    void create(uint64_t account, string salt) {
        auto &&create_acc = create_act{account, std::move(salt)};

        auto &&create_acc_data = bytes();
        create_acc.pack(create_acc_data);
        mocked_context create_acc_ctx(code, code, "create"_n.value, create_acc_data, database,
                                      i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache);
        auto fn = [&]() {
            backend->initialize(&create_acc_ctx);
            const auto &res = backend->call(
                    &create_acc_ctx, "env", "apply", create_acc_ctx.get_receiver(),
                    create_acc_ctx.get_account(),
                    create_acc_ctx.get_action());
        };
        backend->timed_run(wd, fn);
    }

    void createeth(uint64_t account, eth_addr eth_address) {
        auto &&createeth_acc = createeth_act{account, std::move(eth_address)};

        auto &&createeth_acc_data = bytes();
        createeth_acc.pack(createeth_acc_data);
        mocked_context createeth_acc_ctx(code, code, "createeth"_n.value, createeth_acc_data,
                                         database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache,
                                         i256_sec_keyval_cache);
        auto fn = [&]() {
            backend->initialize(&createeth_acc_ctx);
            const auto &res = backend->call(
                    &createeth_acc_ctx, "env", "apply", createeth_acc_ctx.get_receiver(),
                    createeth_acc_ctx.get_account(),
                    createeth_acc_ctx.get_action());
        };
        backend->timed_run(wd, fn);
    }

    void raw(hex_code trx_code, eth_addr sender = "") {
        auto &&raw_action = raw_act{};
        raw_action.trx_code = std::move(trx_code);
        raw_action.sender = std::move(sender);
        auto &&raw_act_data = bytes();
        raw_action.pack(raw_act_data);
        mocked_context raw_act_ctx(code, code, "raw"_n.value, raw_act_data,
                                   database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache,
                                   i256_sec_keyval_cache);
        auto fn = [&]() {
            backend->initialize(&raw_act_ctx);
            const auto &res = backend->call(
                    &raw_act_ctx, "env", "apply", raw_act_ctx.get_receiver(),
                    raw_act_ctx.get_account(),
                    raw_act_ctx.get_action());
        };
        backend->timed_run(wd, fn);
    }

    void rawtrxexe(hex_code trx_param, eth_addr eth_address, eth_addr sender) {
        auto &&rawtrxexe_action = rawtrxexe_act{};
        rawtrxexe_action.trx_param = std::move(trx_param);
        rawtrxexe_action.eth_address = std::move(eth_address);
        rawtrxexe_action.sender = std::move(sender);
        auto &&rawtrxexe_data = bytes();
        rawtrxexe_action.pack(rawtrxexe_data);
        mocked_context rawtrxexe_ctx(code, code, "raw"_n.value, rawtrxexe_data,
                                     database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache,
                                     i256_sec_keyval_cache);
        auto fn = [&]() {
            backend->initialize(&rawtrxexe_ctx);
            const auto &res = backend->call(
                    &rawtrxexe_ctx, "env", "apply", rawtrxexe_ctx.get_receiver(),
                    rawtrxexe_ctx.get_account(),
                    rawtrxexe_ctx.get_action());
        };
        backend->timed_run(wd, fn);
    }

private:
    uint64_t                                 code;
    std::shared_ptr<backend_t>               backend;
    eosio::vm::watchdog                      wd{std::chrono::seconds(3000000)};
    db_type                                  database;
    secondary_key_type<uint64_t>             i64_index;
    secondary_key_type<array<uint128_t, 2>>  i256_index;
    vector<kv_type>                          keyval_cache;
    vector<i64_sec_kv_type>                  i64_sec_keyval_cache;
    vector<i256_sec_kv_type>                 i256_sec_keyval_cache;
};