//
// Created by Vince on 22/3/20.
//

#pragma once

#include <evmc/evmc.h>

namespace vmtest
{
    evmc_result execute(evmc_vm* vm, const evmc_host_interface* host, evmc_host_context* ctx,
                        evmc_revision rev, const evmc_message* msg, const uint8_t* code, size_t code_size) noexcept;
}

