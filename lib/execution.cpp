//
// Created by Vince on 22/3/20.
//
#include <evmc/evmc.hpp>
#include "execution.hpp"
#include "vm.hpp"
#include <memory>
#include "contract/challenge_contract.hpp"

evmc_status_code convert_status(const string& str) {
    if(str == "EVMC_SUCCESS") return EVMC_SUCCESS;
    else if(str == "EVMC_FAILURE") return EVMC_FAILURE;
    else if(str == "EVMC_REVERT") return EVMC_REVERT;
    else if(str == "EVMC_OUT_OF_GAS") return EVMC_OUT_OF_GAS;
    else if(str == "EVMC_INVALID_INSTRUCTION") return EVMC_INVALID_INSTRUCTION;
    else if(str == "EVMC_UNDEFINED_INSTRUCTION") return EVMC_UNDEFINED_INSTRUCTION;
    else if(str == "EVMC_STACK_OVERFLOW") return EVMC_STACK_OVERFLOW;
    else if(str == "EVMC_STACK_UNDERFLOW") return EVMC_STACK_UNDERFLOW;
    else if(str == "EVMC_BAD_JUMP_DESTINATION") return EVMC_BAD_JUMP_DESTINATION;
    else if(str == "EVMC_INVALID_MEMORY_ACCESS") return EVMC_INVALID_MEMORY_ACCESS;
    else if(str == "EVMC_CALL_DEPTH_EXCEEDED") return EVMC_CALL_DEPTH_EXCEEDED;
    else if(str == "EVMC_STATIC_MODE_VIOLATION") return EVMC_STATIC_MODE_VIOLATION;
    else if(str == "EVMC_PRECOMPILE_FAILURE") return EVMC_PRECOMPILE_FAILURE;
    else if(str == "EVMC_CONTRACT_VALIDATION_FAILURE") return EVMC_CONTRACT_VALIDATION_FAILURE;
    else if(str == "EVMC_ARGUMENT_OUT_OF_RANGE") return EVMC_ARGUMENT_OUT_OF_RANGE;
    else if(str == "EVMC_WASM_UNREACHABLE_INSTRUCTION") return EVMC_WASM_UNREACHABLE_INSTRUCTION;
    else if(str == "EVMC_WASM_TRAP") return EVMC_WASM_TRAP;
    else if(str == "EVMC_INTERNAL_ERROR") return EVMC_INTERNAL_ERROR;
    else if(str == "EVMC_REJECTED") return EVMC_REJECTED;
    else if(str == "EVMC_OUT_OF_MEMORY") return EVMC_OUT_OF_MEMORY;
    else throw "unknown status";
}

evmc::bytes32 hex_to_bytes32(const std::string &str) {
    evmc_bytes32 b32 = {};

    auto bytes = hex_to_bytes(str);
    for (auto i = 0; i < 32; i++) {
        b32.bytes[i] = bytes[i];
    }
    return b32;
}

evmc_address hex_to_evmc_address(const std::string &str) {
    evmc_address addr = {};

    auto bytes = hex_to_bytes(str);
    for (auto i = 0; i < 20; i++) {
        addr.bytes[i] = bytes[i];
    }
    return addr;
}

namespace vmtest
{
    evmc_result execute(evmc_vm* /*unused*/, const evmc_host_interface* host, evmc_host_context* ctx,
                        evmc_revision rev, const evmc_message* msg, const uint8_t* code, size_t code_size) noexcept
    {
        vm eos_evm(challenge_wasm, "bpa"_n);
        evmc::HostContext h{*host, ctx};

        eos_evm.link_token({1397703940, "eosio.token"_n});
        auto address = bytes_to_hex_str(msg->destination.bytes, 20);
        auto caller = bytes_to_hex_str(msg->sender.bytes, 20);
        auto origin = bytes_to_hex_str(h.get_tx_context().tx_origin.bytes, 20);
        eos_evm.create("bpb"_n, address);
        eos_evm.create("bpc"_n, caller);
        if (origin != caller) eos_evm.create("bpd"_n, origin);

        auto pre_key = evmc::bytes32{};
        auto  pre_value = h.get_storage(msg->destination, pre_key);
        while (pre_value != evmc::bytes32{}) {
            eos_evm.set_storage(address, {bytes_to_hex_str(pre_key.bytes, 32), bytes_to_hex_str(pre_value.bytes, 32)});
            pre_key = evmc::bytes32{hex_to_ui64(bytes_to_hex_str(pre_key.bytes, 32)) + 1};
            pre_value = h.get_storage(msg->destination, pre_key);
        }

        try {
            auto result = eos_evm.rawtest(
                address,
                caller,
                bytes_to_hex_str(code, code_size),
                bytes_to_hex_str(msg->input_data, msg->input_size),
                int_to_hex(msg->gas),
                bytes_to_hex_str(h.get_tx_context().tx_gas_price.bytes, 32),
                origin,
                bytes_to_hex_str(msg->value.bytes, 32),
                {(int)h.get_tx_context().block_number, (uint64_t)h.get_tx_context().block_timestamp}
            );

            auto status_code = convert_status(result.status_code);
            auto gas_left = string_to_i64(result.gas_left);

            std::for_each(result.output.begin(), result.output.end(), [](char &c) {
                c = ::tolower(c);
            });

            auto output_bytes = hex_to_bytes(result.output);

            auto storage_map = eos_evm.get_storage(address);
            for (auto &e: storage_map) {
                h.set_storage(msg->destination, hex_to_bytes32(e.first), hex_to_bytes32(e.second));
            }


            if (!result.log.empty()) {
                std::map<std::string, std::string> ret;
                Json::Value root;
                JSONCPP_STRING err;
                Json::CharReaderBuilder builder;
                const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
                if (!reader->parse(result.log.c_str(), result.log.c_str() + result.log.size(), &root, &err)) {
                    cerr << "pass error" << std::endl;
                }

                if (!root.isArray()) {
                    cerr << "root is not an array" << std::endl;
                } else {
                    for (auto &e: root) {
                        auto addr = hex_to_evmc_address(e["address"].asString());
                        auto log_data = hex_to_bytes(e["data"].asString());
                        auto topics = e["topics"];
                        if (!topics.isArray()) {
                            std::cout << "topics is not an array" << std::endl;
                        } else {
                            vector<evmc::bytes32> topic_bytes{};
                            for (auto &i: topics) {
                                topic_bytes.emplace_back(hex_to_bytes32(i.asString()));
                            }
                            h.emit_log(addr, log_data.data(), log_data.size(), topic_bytes.data(), topic_bytes.size());
                        }
                    }
                }
            }
            return evmc::make_result(status_code, gas_left, output_bytes.data(), output_bytes.size());
        } catch(exception& ex) {
            cerr << ex.what() << endl;
            return evmc::make_result(EVMC_INTERNAL_ERROR, 0, nullptr, 0);
        }
    }
}