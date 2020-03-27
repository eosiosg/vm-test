//
// Created by Vince on 22/3/20.
//
#include "execution.hpp"
#include "../include/eosevm.h"

extern "C" {
EVMC_EXPORT evmc_vm* evmc_create_eosevm() noexcept
{
    static constexpr auto destroy = [](evmc_vm*) noexcept {};
    static constexpr auto get_capabilities = [](evmc_vm*) noexcept
    {
        return evmc_capabilities_flagset{EVMC_CAPABILITY_EVM1};
    };

    static auto instance = evmc_vm{
            EVMC_ABI_VERSION,
            "eosevm",
            PROJECT_VERSION,
            destroy,
            vmtest::execute,
            get_capabilities,
            /* set_option(): */ nullptr,
    };
    return &instance;
}
}