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
        eosio::vm::watchdog wd{std::chrono::seconds(3)};
        // Point the backend to the allocator you want it to use.
        backend.set_wasm_allocator(&wa);
        backend.initialize();
        // Resolve the host functions indices.
        db_type database;
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
        rhf_t::template add<mocked_context, &mocked_context::prints, eosio::vm::wasm_allocator>("env", "prints");
        rhf_t::template add<mocked_context, &mocked_context::printui, eosio::vm::wasm_allocator>("env", "printui");
        rhf_t::template add<mocked_context, &mocked_context::printhex, eosio::vm::wasm_allocator>("env", "printhex");
        rhf_t::template add<mocked_context, &mocked_context::__ashlti3, eosio::vm::wasm_allocator>("env", "__ashlti3");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_lowerbound, eosio::vm::wasm_allocator>("env", "db_idx256_lowerbound");
        rhf_t::template add<mocked_context, &mocked_context::db_find_i64, eosio::vm::wasm_allocator>("env", "db_find_i64");
        rhf_t::template add<mocked_context, &mocked_context::printi, eosio::vm::wasm_allocator>("env", "printi");
        rhf_t::template add<mocked_context, &mocked_context::require_auth, eosio::vm::wasm_allocator>("env", "require_auth");
        rhf_t::template add<mocked_context, &mocked_context::current_receiver, eosio::vm::wasm_allocator>("env", "current_receiver");
        rhf_t::template add<mocked_context, &mocked_context::db_update_i64, eosio::vm::wasm_allocator>("env", "db_update_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_find_primary, eosio::vm::wasm_allocator>("env", "db_idx256_find_primary");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_update, eosio::vm::wasm_allocator>("env", "db_idx256_update");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_find_primary, eosio::vm::wasm_allocator>("env", "db_idx64_find_primary");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_update, eosio::vm::wasm_allocator>("env", "db_idx64_update");
        rhf_t::template add<mocked_context, &mocked_context::send_inline, eosio::vm::wasm_allocator>("env", "send_inline");
        rhf_t::template add<mocked_context, &mocked_context::action_data_size, eosio::vm::wasm_allocator>("env", "action_data_size");
        rhf_t::template add<mocked_context, &mocked_context::read_action_data, eosio::vm::wasm_allocator>("env", "read_action_data");
        rhf_t::template add<mocked_context, &mocked_context::eosio_assert_code, eosio::vm::wasm_allocator>("env", "eosio_assert_code");
        rhf_t::template add<mocked_context, &mocked_context::db_get_i64, eosio::vm::wasm_allocator>("env", "db_get_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_lowerbound_i64, eosio::vm::wasm_allocator>("env", "db_lowerbound_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_store_i64, eosio::vm::wasm_allocator>("env", "db_store_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx256_store, eosio::vm::wasm_allocator>("env", "db_idx256_store");
        rhf_t::template add<mocked_context, &mocked_context::db_previous_i64, eosio::vm::wasm_allocator>("env", "db_previous_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_end_i64, eosio::vm::wasm_allocator>("env", "db_end_i64");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_lowerbound, eosio::vm::wasm_allocator>("env", "db_idx64_lowerbound");
        rhf_t::template add<mocked_context, &mocked_context::assert_sha256, eosio::vm::wasm_allocator>("env", "assert_sha256");
        rhf_t::template add<mocked_context, &mocked_context::assert_sha1, eosio::vm::wasm_allocator>("env", "assert_sha1");
        rhf_t::template add<mocked_context, &mocked_context::assert_sha512, eosio::vm::wasm_allocator>("env", "assert_sha512");
        rhf_t::template add<mocked_context, &mocked_context::assert_ripemd160, eosio::vm::wasm_allocator>("env", "assert_ripemd160");
        rhf_t::template add<mocked_context, &mocked_context::sha256, eosio::vm::wasm_allocator>("env", "sha256");
        rhf_t::template add<mocked_context, &mocked_context::sha1, eosio::vm::wasm_allocator>("env", "sha1");
        rhf_t::template add<mocked_context, &mocked_context::sha512, eosio::vm::wasm_allocator>("env", "sha512");
        rhf_t::template add<mocked_context, &mocked_context::ripemd160, eosio::vm::wasm_allocator>("env", "ripemd160");
        rhf_t::template add<mocked_context, &mocked_context::recover_key, eosio::vm::wasm_allocator>("env", "recover_key");
        rhf_t::template add<mocked_context, &mocked_context::assert_recover_key, eosio::vm::wasm_allocator>("env", "assert_recover_key");
        rhf_t::template add<mocked_context, &mocked_context::set_blockchain_parameters_packed, eosio::vm::wasm_allocator>("env", "set_blockchain_parameters_packed");
        rhf_t::template add<mocked_context, &mocked_context::get_blockchain_parameters_packed, eosio::vm::wasm_allocator>("env", "get_blockchain_parameters_packed");
        rhf_t::template add<mocked_context, &mocked_context::set_proposed_producers, eosio::vm::wasm_allocator>("env", "set_proposed_producers");
        rhf_t::template add<mocked_context, &mocked_context::current_time, eosio::vm::wasm_allocator>("env", "current_time");
        rhf_t::template add<mocked_context, &mocked_context::get_active_producers, eosio::vm::wasm_allocator>("env", "get_active_producers");
        rhf_t::template add<mocked_context, &mocked_context::db_idx64_store, eosio::vm::wasm_allocator>("env", "db_idx64_store");
        rhf_t::template add<mocked_context, &mocked_context::__multi3, eosio::vm::wasm_allocator>("env", "__multi3");

        rhf_t::resolve(backend.get_module());

        // check action
        mocked_context mc0(".bpa"_n.value, ".bpa"_n.value, "check"_n.value, bytes(), database);
        backend.call(&mc0, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "check"_n.value);

        // create action
        struct create_type {
            uint64_t eos_account;
            string   account;
        };
        auto && create_act = create_type{"bpb"_n.value, "aaaaa"};
        auto && create_data = bytes();
        create_data.resize(sizeof(create_act));
        memcpy(&create_data[0], &create_act, sizeof(create_act));
        mocked_context mc1(".bpa"_n.value, ".bpa"_n.value, "create"_n.value, create_data, database);
        backend.call(&mc1, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "create"_n.value);

        // updateeth action
        struct updateeth_type {
            sha256_type eth_address;
            name        eos_account;
        };
        auto && updateeth_act = updateeth_type{"a", "bpc"_n.value};
        auto && updateeth_data = bytes();
        updateeth_data.resize(sizeof(updateeth_act));
        memcpy(&updateeth_data[0], &updateeth_act, sizeof(updateeth_act));
        mocked_context mc2(".bpa"_n.value, ".bpa"_n.value, "updateeth"_n.value, updateeth_data, database);
        backend.call(&mc2, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "updateeth"_n.value);

        // setcode action
        struct setcode_type {
            eth_addr eth_address;
            hex_code evm_code;
        };
        auto && setcode_act = setcode_type{};
        setcode_act.eth_address = "000000000000000000000000473663c9fe1357de90ae121ab1ebcb332c7395d1";
        setcode_act.evm_code = "6080604052600436106100ba576000357c0100000000000000000000000000000000000000000000000000000000900463ffffffff16806306fdde03146100bf578063095ea7b31461014f57806318160ddd146101b457806323b872dd146101df57806327e235e314610264578063313ce567146102bb5780635c658165146102ec57806370a082311461036357806395d89b41146103ba578063a9059cbb1461044a578063d74a99d4146104af578063dd62ed3e14610575575b600080fd5b3480156100cb57600080fd5b506100d46105ec565b6040518080602001828103825283818151815260200191508051906020019080838360005b838110156101145780820151818401526020810190506100f9565b50505050905090810190601f1680156101415780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b34801561015b57600080fd5b5061019a600480360381019080803573ffffffffffffffffffffffffffffffffffffffff1690602001909291908035906020019092919050505061068a565b604051808215151515815260200191505060405180910390f35b3480156101c057600080fd5b506101c961077c565b6040518082815260200191505060405180910390f35b3480156101eb57600080fd5b5061024a600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190803573ffffffffffffffffffffffffffffffffffffffff16906020019092919080359060200190929190505050610782565b604051808215151515815260200191505060405180910390f35b34801561027057600080fd5b506102a5600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190505050610a1c565b6040518082815260200191505060405180910390f35b3480156102c757600080fd5b506102d0610a34565b604051808260ff1660ff16815260200191505060405180910390f35b3480156102f857600080fd5b5061034d600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190803573ffffffffffffffffffffffffffffffffffffffff169060200190929190505050610a47565b6040518082815260200191505060405180910390f35b34801561036f57600080fd5b506103a4600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190505050610a6c565b6040518082815260200191505060405180910390f35b3480156103c657600080fd5b506103cf610ab5565b6040518080602001828103825283818151815260200191508051906020019080838360005b8381101561040f5780820151818401526020810190506103f4565b50505050905090810190601f16801561043c5780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b34801561045657600080fd5b50610495600480360381019080803573ffffffffffffffffffffffffffffffffffffffff16906020019092919080359060200190929190505050610b53565b604051808215151515815260200191505060405180910390f35b3480156104bb57600080fd5b5061057360048036038101908080359060200190929190803590602001908201803590602001908080601f0160208091040260200160405190810160405280939291908181526020018383808284378201915050505050509192919290803560ff169060200190929190803590602001908201803590602001908080601f0160208091040260200160405190810160405280939291908181526020018383808284378201915050505050509192919290505050610cac565b005b34801561058157600080fd5b506105d6600480360381019080803573ffffffffffffffffffffffffffffffffffffffff169060200190929190803573ffffffffffffffffffffffffffffffffffffffff169060200190929190505050610d46565b6040518082815260200191505060405180910390f35b60038054600181600116156101000203166002900480601f0160208091040260200160405190810160405280929190818152602001828054600181600116156101000203166002900480156106825780601f1061065757610100808354040283529160200191610682565b820191906000526020600020905b81548152906001019060200180831161066557829003601f168201915b505050505081565b600081600260003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925846040518082815260200191505060405180910390a36001905092915050565b60005481565b600080600260008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054905082600160008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054101580156108535750828110155b151561085e57600080fd5b82600160008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000206000828254019250508190555082600160008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825403925050819055507fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff8110156109ab5782600260008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825403925050819055505b8373ffffffffffffffffffffffffffffffffffffffff168573ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef856040518082815260200191505060405180910390a360019150509392505050565b60016020528060005260406000206000915090505481565b600460009054906101000a900460ff1681565b6002602052816000526040600020602052806000526040600020600091509150505481565b6000600160008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020549050919050565b60058054600181600116156101000203166002900480601f016020809104026020016040519081016040528092919081815260200182805460018160011615610100020316600290048015610b4b5780601f10610b2057610100808354040283529160200191610b4b565b820191906000526020600020905b815481529060010190602001808311610b2e57829003601f168201915b505050505081565b600081600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205410151515610ba357600080fd5b81600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000206000828254039250508190555081600160008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825401925050819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef846040518082815260200191505060405180910390a36001905092915050565b83600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002081905550836000819055508260039080519060200190610d0d929190610dcd565b5081600460006101000a81548160ff021916908360ff1602179055508060059080519060200190610d3f929190610dcd565b5050505050565b6000600260008473ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054905092915050565b828054600181600116156101000203166002900490600052602060002090601f016020900481019282601f10610e0e57805160ff1916838001178555610e3c565b82800160010185558215610e3c579182015b82811115610e3b578251825591602001919060010190610e20565b5b509050610e499190610e4d565b5090565b610e6f91905b80821115610e6b576000816000905550600101610e53565b5090565b905600a165627a7a72305820e55770e16d6fdfeef46f27fd89f7be39d403b35d937d11d065ff5e09a53062f30029";
        auto && setcode_data = bytes();
        setcode_data.resize(sizeof(setcode_act));
        memcpy(&setcode_data[0], &setcode_act, sizeof(setcode_act));
        mocked_context mc3(".bpa"_n.value, ".bpa"_n.value, "setcode"_n.value, setcode_data, database);
        backend.call(&mc3, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "setcode"_n.value);

        // rawtrxexe action
        struct rawtrxexe_type {
            hex_code trx_param;
            eth_addr eth_address;
            eth_addr sender;
        };
        auto && rawtrxexe_act = rawtrxexe_type{};
        rawtrxexe_act.trx_param = "18160ddd";
        rawtrxexe_act.eth_address = "ee81d972ab777d73106a045d23c98199443a2e9e";
        rawtrxexe_act.sender = "ee81d972ab777d73106a045d23c98199443a2e9e";
        auto && rawtrxexe_data = bytes();
        rawtrxexe_data.resize(sizeof(rawtrxexe_act));
        memcpy(&rawtrxexe_data[0], &rawtrxexe_act, sizeof(rawtrxexe_act));
        mocked_context mc4(".bpa"_n.value, ".bpa"_n.value, "rawtrxexe"_n.value, rawtrxexe_data, database);
        backend.call(&mc4, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "rawtrxexe"_n.value);

        // hexcodegen action
        mocked_context mc5(".bpa"_n.value, ".bpa"_n.value, "hexcodegen"_n.value, bytes(), database);
        backend.call(&mc5, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "hexcodegen"_n.value);

        // raw action
        struct raw_type {
            hex_code trx_code;
            eth_addr sender;
        };
        auto && raw_act = raw_type{};
        raw_act.trx_code = "f8ab018609184e72a0008302710094763c40c946471528d2ed5f12ee81d972ab777d7380b844a9059cbb000000000000000000000000d81f4358cb8cab53d005e7f47c7ba3f5116000a6000000000000000000000000000000000000000000000000000000000000006425a074fb87778fdcd2853476f1559fc797b8f1f6511fd46a5740ad398dab091544d7a00dd9490d6984ec9814d8b6aba6146e7e25e10f44bcb18e1b678f23f4d7b88f38";
        raw_act.sender = "";
        auto && raw_data = bytes();
        raw_data.resize(sizeof(raw_act));
        memcpy(&raw_data[0], &raw_act, sizeof(raw_act));
        mocked_context mc6(".bpa"_n.value, ".bpa"_n.value, "raw"_n.value, raw_data, database);
        backend.call(&mc6, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "raw"_n.value);

        // rawtest action
        struct rawtest_type {
            hex_code hexcode;
        };
        auto && rawtest_act = rawtest_type{};
        rawtest_act.hexcode = "d74a99d400000000000000000000000000000000000000000000000000000000000027100000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000000000000000000000000000000000000000000a746f6b656e20746573740000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000035359530000000000000000000000000000000000000000000000000000000000";
        auto && rawtest_data = bytes();
        rawtest_data.resize(sizeof(rawtest_act));
        memcpy(&rawtest_data[0], &rawtest_act, sizeof(rawtest_act));
        mocked_context mc7(".bpa"_n.value, ".bpa"_n.value, "rawtest"_n.value, rawtest_data, database);
        backend.call(&mc7, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "rawtest"_n.value);

        struct asset {
            uint64_t amount;
            uint64_t sym;
        };


        // verifysig action
        struct verifysig_type {
            hex_code trx_code;
        };
        auto && verifysig_act = verifysig_type{};
        verifysig_act.trx_code = "d74a99d400000000000000000000000000000000000000000000000000000000000027100000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000000000000000000000000000000000000000000a746f6b656e20746573740000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000035359530000000000000000000000000000000000000000000000000000000000";
        auto && verifysig_data = bytes();
        verifysig_data.resize(sizeof(verifysig_act));
        memcpy(&verifysig_data[0], &verifysig_act, sizeof(verifysig_act));
        mocked_context mc8(".bpa"_n.value, ".bpa"_n.value, "verifysig"_n.value, verifysig_data, database);
        backend.call(&mc8, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "verifysig"_n.value);

        // withdraw action
        struct withdraw_type {
            name  eos_account;
            asset amount;
        };
        auto && withdraw_act = withdraw_type{};
        withdraw_act.eos_account = "bpc"_n.value;
        withdraw_act.amount = {10000, 1397703938};
        auto && withdraw_data = bytes();
        withdraw_data.resize(sizeof(withdraw_act));
        memcpy(&withdraw_data[0], &withdraw_act, sizeof(withdraw_act));
        mocked_context mc9(".bpa"_n.value, ".bpa"_n.value, "transfers"_n.value, withdraw_data, database);
        backend.call(&mc9, "env", "apply", ".bpa"_n.value, ".bpa"_n.value, "transfers"_n.value);

    };
};