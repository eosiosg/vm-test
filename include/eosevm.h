//
// Created by Vince on 22/3/20.
//

#ifndef VM_TEST_EOSEVM_H
#define VM_TEST_EOSEVM_H

#include <evmc/evmc.h>
#include <evmc/utils.h>

#if __cplusplus
extern "C" {
#endif

EVMC_EXPORT struct evmc_vm* evmc_create_eosevm(void) EVMC_NOEXCEPT;

#if __cplusplus
}
#endif

#endif //VM_TEST_EOSEVM_H
