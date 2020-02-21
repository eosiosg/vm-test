//
// Created by Xiaofeng Qian on 21/2/20.
//
#include <eosio/vm/backend.hpp>
#include <eosio/vm/watchdog.hpp>
#include <gtest/gtest.h>
#include <fstream>
namespace eosio { namespace vm {
template <>
struct wasm_type_converter<const char *> : linear_memory_access {
  const char *from_wasm(const void *val) {
    validate_c_str(val);
    return static_cast<const char *>(val);
  }
};
}}
void eosio_assert(bool test, const char *msg) {
  if (!test) {
    std::cout << msg << std::endl;
    throw 0;
  }
}

struct mocked_host_methods{
//  void print_name(const char* nm) { std::cout << "Name : " << nm << " " << field << "\n"; }
  static void* memset(void* ptr, int x, size_t n) { return ::memset(ptr, x, n); }
};

using backend_t = eosio::vm::backend<mocked_host_methods>;
using rhf_t = eosio::vm::registered_host_functions<mocked_host_methods>;


class eosvm_tester: public testing::Test{
protected:
  void execute_contract(const std::string &path){

    std::ifstream input(path,std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = input.tellg();
    std::vector<char > tmp(pos);
    input.seekg(0, std::ios::beg);
    input.read(&tmp[0], pos);

    std::vector<uint8_t> wasm;

    std::copy(tmp.begin(),tmp.end(),std::back_inserter(wasm));

    rhf_t::add<nullptr_t, &mocked_host_methods::memset, eosio::vm::wasm_allocator>(
        "env", "memset");
    rhf_t::add<nullptr_t, &eosio_assert, eosio::vm::wasm_allocator>("env", "eosio_assert");

    backend_t backend(wasm,rhf_t{});
    eosio::vm::wasm_allocator wa;
    eosio::vm::watchdog  wd{std::chrono::seconds(3)};
    // Point the backend to the allocator you want it to use.
    backend.set_wasm_allocator(&wa);
    backend.initialize();
    // Resolve the host functions indices.

    // Instaniate a "host"
    mocked_host_methods hm;
    uint64_t a = 3;
    uint64_t b = 4;
    backend(&hm, "env", "apply", a,b);
  }
};