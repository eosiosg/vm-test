//
// Created by Vince on 25/3/20.
//
#pragma once

#include <eosio/vm/backend.hpp>
#include <memory>
#include <utility>
#include <eosio/vm/watchdog.hpp>
#include <eosio/vm/execution_context.hpp>
#include <fstream>
#include "name.hpp"
#include "mocked_context.hpp"
#include <openssl/sha.h>

typedef string eth_addr;
typedef string hex_code;


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
    eosio::name contract;
};

struct asset {
    int64_t amount;
    uint64_t sym;
};

struct linktoken_act {
    extended_symbol contract;
    void pack(vector<char>& dest) {
        dest.resize(sizeof(contract));
        memcpy(&dest[0], &contract , sizeof(contract ));
    }
};

struct create_act {
    eosio::name eos_account;
    string      salt;
    void pack(vector<char>& dest) {
        dest.resize(sizeof(eos_account));
        memcpy(&dest[0], &eos_account , sizeof(eos_account ));
        pack_string(salt, dest);
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

struct rawtest_act {
    string address;
    string caller;
    hex_code code;
    string data;
    string gas;
    string gas_price;
    string origin;
    string value;
    void pack(vector<char>& dest) {
        pack_string(address, dest);
        pack_string(caller, dest);
        pack_string(code, dest);
        pack_string(data, dest);
        pack_string(gas, dest);
        pack_string(gas_price, dest);
        pack_string(origin, dest);
        pack_string(value, dest);
    }
};

struct withdraw_act {
    eosio::name eos_account;
    asset amount;
    void pack(vector<char>& dest) {
        dest.resize(sizeof(eos_account) + sizeof(amount));
        memcpy(&dest[0], &eos_account , sizeof(eos_account ));
        memcpy(&dest[sizeof(eos_account)], &amount , sizeof(amount ));
    }
};

struct action_result {
    string  status_code;
    string  gas_left;
    string  output;
    string  log;
};

class vm {
public:
    vm(const std::string &path, eosio::name account): code(account) {

        std::ifstream input(path, std::ios::binary | std::ios::ate);
        std::ifstream::pos_type pos = input.tellg();
        std::vector<char> tmp(pos);
        input.seekg(0, std::ios::beg);
        input.read(&tmp[0], pos);

        std::copy(tmp.begin(), tmp.end(), std::back_inserter(wasm));
    }

    void init_backend(backend_t& bkend) {

        // Point the backend to the allocator you want it to use.
        bkend.set_wasm_allocator(&wa);
        // Resolve the host functions indices.
        output = {};
        keyval_cache = {};
        i64_sec_keyval_cache = {};
        i256_sec_keyval_cache = {};

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
        rhf_t::template add<mocked_context, &mocked_context::__multi3, eosio::vm::wasm_allocator>("env", "__multi3");
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
        rhf_t::template add<mocked_context, &mocked_context::db_next_i64, eosio::vm::wasm_allocator>("env", "db_next_i64");
        rhf_t::template add<mocked_context, &mocked_context::prints, eosio::vm::wasm_allocator>("env", "prints");
        rhf_t::template add<mocked_context, &mocked_context::printhex, eosio::vm::wasm_allocator>("env", "printhex");
        rhf_t::template add<mocked_context, &mocked_context::printui, eosio::vm::wasm_allocator>("env", "printui");
        rhf_t::template add<mocked_context, &mocked_context::printi, eosio::vm::wasm_allocator>("env", "printi");
        rhf_t::template add<mocked_context, &mocked_context::db_store_i64, eosio::vm::wasm_allocator>("env", "db_store_i64");
        rhf_t::template add<mocked_context, &mocked_context::send_inline, eosio::vm::wasm_allocator>("env", "send_inline");
        rhf_t::template add<mocked_context, &mocked_context::db_update_i64, eosio::vm::wasm_allocator>("env", "db_update_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_find_primary, eosio::vm::wasm_allocator>("env", "db_idx256_find_primary");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_update, eosio::vm::wasm_allocator>("env", "db_idx256_update");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_find_primary, eosio::vm::wasm_allocator>("env", "db_idx64_find_primary");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_update, eosio::vm::wasm_allocator>("env", "db_idx64_update");
        rhf_t::template add<mocked_context, &mocked_context::action_data_size, eosio::vm::wasm_allocator>("env", "action_data_size");
        rhf_t::template add<mocked_context, &mocked_context::read_action_data, eosio::vm::wasm_allocator>("env", "read_action_data");
        rhf_t::template add<mocked_context, &mocked_context::eosio_assert_code, eosio::vm::wasm_allocator>("env", "eosio_assert_code");
        rhf_t::template add<mocked_context, &mocked_context::tapos_block_num, eosio::vm::wasm_allocator>("env", "tapos_block_num");
        rhf_t::template add<mocked_context, &mocked_context::tapos_block_prefix, eosio::vm::wasm_allocator>("env", "tapos_block_prefix");
        rhf_t::template add<mocked_context, &mocked_context::db_get_i64, eosio::vm::wasm_allocator>("env", "db_get_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_store, eosio::vm::wasm_allocator>("env", "db_idx256_store");
        rhf_t::template add<mocked_context, &mocked_context::db_previous_i64, eosio::vm::wasm_allocator>("env", "db_previous_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_end_i64, eosio::vm::wasm_allocator>("env", "db_end_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_remove_i64, eosio::vm::wasm_allocator>("env", "db_remove_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_remove, eosio::vm::wasm_allocator>("env", "db_idx256_remove");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_store, eosio::vm::wasm_allocator>("env", "db_idx64_store");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_next, eosio::vm::wasm_allocator>("env", "db_idx256_next");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_remove, eosio::vm::wasm_allocator>("env", "db_idx64_remove");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_lowerbound, eosio::vm::wasm_allocator>("env", "db_idx64_lowerbound");

        rhf_t::resolve(bkend.get_module());
    };

    void link_token(extended_symbol ex_sym) {
        backend_t backend(wasm);
        init_backend(backend);

        auto &&link_token = linktoken_act{ex_sym.sym, ex_sym.contract};

        auto &&link_token_data = bytes();
        link_token.pack(link_token_data);
        mocked_context link_token_ctx(code, code, "linktoken"_n, link_token_data, database,
                                      i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache, output);
        auto fn = [&]() {
            backend.initialize(&link_token_ctx);
            const auto &res = backend.call(
                    &link_token_ctx, "env", "apply", link_token_ctx.get_receiver(),
                    link_token_ctx.get_account(),
                    link_token_ctx.get_action());
        };
        backend.timed_run(wd, fn);
    }

    void create(eosio::name eos_account, const string& eth_address) {
        backend_t backend(wasm);
        init_backend(backend);
        auto addr = eth_address;
        if (eth_address.find("0x") == 0) addr = addr.substr(2);
        auto &&create_acc = create_act{eos_account, addr};

        auto &&create_acc_data = bytes();
        create_acc.pack(create_acc_data);
        mocked_context create_acc_ctx(code, code, "create"_n, create_acc_data, database,
                                      i64_index, i256_index, keyval_cache, i64_sec_keyval_cache, i256_sec_keyval_cache, output);
        auto fn = [&]() {
            backend.initialize(&create_acc_ctx);
            const auto &res = backend.call(
                    &create_acc_ctx, "env", "apply", create_acc_ctx.get_receiver(),
                    create_acc_ctx.get_account(),
                    create_acc_ctx.get_action());
        };
        backend.timed_run(wd, fn);
    }

    action_result raw(const hex_code& trx_code, const eth_addr& sender = "") {
        backend_t backend(wasm);
        init_backend(backend);

        auto &&raw_action = raw_act{};
        raw_action.trx_code = trx_code;
        raw_action.sender = sender;
        auto &&raw_act_data = bytes();
        raw_action.pack(raw_act_data);
        mocked_context raw_act_ctx(code, code, "raw"_n, raw_act_data,
                                   database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache,
                                   i256_sec_keyval_cache, output);
        auto fn = [&]() {
            backend.initialize(&raw_act_ctx);
            const auto &res = backend.call(
                    &raw_act_ctx, "env", "apply", raw_act_ctx.get_receiver(),
                    raw_act_ctx.get_account(),
                    raw_act_ctx.get_action());
        };
        backend.timed_run(wd, fn);
        action_result ret;
        ret.status_code = raw_act_ctx.output["status_code"];
        ret.output = raw_act_ctx.output["output"];
        ret.gas_left = raw_act_ctx.output["gas_left"];
        ret.log = raw_act_ctx.output["log"];
        return ret;
    }

    action_result rawtest(const string& address, const string& caller, const hex_code& bytecode, const string& data, const string& gas, const string& gas_price, const string& origin,  const string& value) {
        backend_t backend(wasm);
        init_backend(backend);

        auto &&rawtest_action = rawtest_act{};
        rawtest_action.address = address;
        rawtest_action.caller = caller;
        rawtest_action.code = bytecode;
        rawtest_action.data = data;
        rawtest_action.gas = gas;
        rawtest_action.gas_price = gas_price;
        rawtest_action.origin = origin;
        rawtest_action.value = value;
        auto &&rawtest_act_data = bytes();
        rawtest_action.pack(rawtest_act_data);

        mocked_context rawtest_act_ctx(code, code, "rawtest"_n, rawtest_act_data,
                                       database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache,
                                       i256_sec_keyval_cache, output);
        auto fn = [&]() {
            backend.initialize(&rawtest_act_ctx);
            const auto &res = backend.call(
                    &rawtest_act_ctx, "env", "apply", rawtest_act_ctx.get_receiver(),
                    rawtest_act_ctx.get_account(),
                    rawtest_act_ctx.get_action());
        };
        backend.timed_run(wd, fn);
        action_result ret;
        ret.status_code = rawtest_act_ctx.output["status_code"];
        ret.output = rawtest_act_ctx.output["output"];
        ret.gas_left = rawtest_act_ctx.output["gas_left"];
        if (output.find("log") != output.end()) {
            ret.log = rawtest_act_ctx.output["log"];
        }
        return ret;
    }

    void withdraw(eosio::name eos_account, asset amount) {
        backend_t backend(wasm);
        init_backend(backend);

        auto &&withdraw_action = withdraw_act{};
        withdraw_action.eos_account = eos_account;
        withdraw_action.amount = amount;
        auto &&withdraw_data = bytes();
        withdraw_action.pack(withdraw_data);
        mocked_context withdraw_ctx(code, code, "withdraw"_n, withdraw_data,
                                    database, i64_index, i256_index, keyval_cache, i64_sec_keyval_cache,
                                    i256_sec_keyval_cache, output);
        auto fn = [&]() {
            backend.initialize(&withdraw_ctx);
            const auto &res = backend.call(
                    &withdraw_ctx, "env", "apply", withdraw_ctx.get_receiver(),
                    withdraw_ctx.get_account(),
                    withdraw_ctx.get_action());
        };
        backend.timed_run(wd, fn);
    }

    vector<array<uint128_t, 2>> get_addresses() {
        vector<array<uint128_t, 2>> ret;
        auto i256_tb = i256_index.find(pair{code, "account"_n});
        if (i256_tb == i256_index.end()) {
            cout << "no such table" << endl;
            return ret;
        }

        ret.reserve(i256_tb->second.size());
        for (auto& e :i256_tb->second) {
            ret.emplace_back(e.second);
        }
        return ret;
    }

    map<string, string> get_storage(const array<uint128_t, 2>& key256) {
        map<string, string> m{};

        auto i256_tb = i256_index.find(pair{code, "account"_n});
        if (i256_tb == i256_index.end()) {
            cout << "no such table" << endl;
            return m;
        }

        auto found = false;
        uint64_t pid;
        for (auto& e :i256_tb->second) {
            if (e.second == key256) {
                pid = e.first;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "no such key i256_index" << endl;
            return m;
        }
        auto tb = database.find(pair{eosio::name(pid), "accountstate"_n});
        if (tb == database.end()) {
            cout << "no such key in db" << endl;
            return m;
        }
        for (auto &i: tb->second) {
            auto str = bytes_to_hex(i.second.data(), i.second.size());
            string key(str.data()+16, +64);
            string value(str.data()+80, 64);
            m[key] = value;
        }
        return m;
    }

    map<string, string> get_storage(const string& dest) {
        map<string, string> m{};

        string padding_sender;
        padding_sender.resize(64);
        char zero = '0';
        for (auto i = 0; i < 64; i++) {
            if (i >= 24) {
                padding_sender[i] = dest[i - 24 + 2];
            } else {
                padding_sender[i] = zero;
            }
        }
        auto high_sender = string(padding_sender.data(), 32);
        auto low_sender = string(padding_sender.data()+32, 32);

        array<uint128_t, 2> key256 = {hex_to_u128(high_sender), hex_to_u128(low_sender)};


        auto i256_tb = i256_index.find(pair{code, "account"_n});
        if (i256_tb == i256_index.end()) {
            cout << "no such table" << endl;
            return m;
        }

        auto found = false;
        uint64_t pid;
        for (auto& e :i256_tb->second) {
            if (e.second == key256) {
                pid = e.first;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "no such key i256_index" << endl;
            return m;
        }
        auto tb = database.find(pair{eosio::name(pid), "accountstate"_n});
        if (tb == database.end()) {
            cout << "no such key in db" << endl;
            return m;
        }
        for (auto &i: tb->second) {
            auto str = bytes_to_hex(i.second.data(), i.second.size());
            string key(str.data()+16, +64);
            string value(str.data()+80, 64);
            m[key] = value;
        }
        return m;
    }

    void print_tables() {
        database.print_all();
        i256_index.print_all();
    }

private:
    eosio::name                              code;
    std::vector<uint8_t>                     wasm;
    eosio::vm::wasm_allocator                wa;
    eosio::vm::watchdog                      wd{std::chrono::seconds(3000000)};
    db_type                                  database;
    secondary_key_type<uint64_t>             i64_index;
    secondary_key_type<array<uint128_t, 2>>  i256_index;
    vector<kv_type>                          keyval_cache;
    vector<i64_sec_kv_type>                  i64_sec_keyval_cache;
    vector<i256_sec_kv_type>                 i256_sec_keyval_cache;
    map<string, string>                      output;
};
