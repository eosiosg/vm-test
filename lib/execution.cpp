//
// Created by Vince on 22/3/20.
//
#include <evmc/evmc.hpp>
#include "execution.hpp"
#include "vm.hpp"
#include <memory>

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

namespace vmtest
{
    evmc_result execute(evmc_vm* /*unused*/, const evmc_host_interface* host, evmc_host_context* ctx,
                        evmc_revision rev, const evmc_message* msg, const uint8_t* code, size_t code_size) noexcept
    {
        vm vm(std::string("contract/challenge/eos_evm.wasm"), "bpa"_n);

        string trx(code, code + code_size);
        auto result = vm.raw(trx);

        auto status_code = convert_status(result.status_code);
        auto gas_left = stoi(result.gas_left);

        auto output_data = result.output.data();
        auto output_size = result.output.size();


        return evmc::make_result(status_code, gas_left, (unsigned char *)output_data, output_size);
    }
}