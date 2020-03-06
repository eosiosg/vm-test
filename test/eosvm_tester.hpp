//
// Created by Xiaofeng Qian on 21/2/20.
//
#include <eosio/vm/backend.hpp>
#include <eosio/vm/watchdog.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include "name.hpp"

namespace eosio {
namespace vm {
template <> struct wasm_type_converter<const char *> : linear_memory_access {
  const char *from_wasm(const void *val) {
    validate_c_str(val);
    return static_cast<const char *>(val);
  }
  const void * to_wasm(const char *val) {
    validate_ptr<const char*>(val, 1);
    return val;
  }
};

template <> struct wasm_type_converter<char *> : linear_memory_access {
  char *from_wasm(void *val) {
    validate_c_str(val);
    return static_cast<char *>(val);
  }

  void *to_wasm(char *val) {
    validate_ptr<char>(val, 1);
    return val;
  }
};

} // namespace vm
} // namespace eosio

void prints(char *str) { std::cout << str << std::endl; }
void printui(uint64_t val) { std::cout << val << std::endl; }

void eosio_assert(bool test, const char *msg) {
  if (!test) {
    std::cout << msg << std::endl;
    throw 0;
  }
}

void eosio_assert_code(bool condition, uint64_t error_code) {
  if(!condition){
    std::cout << error_code << std::endl;
    throw 0;
  }
}

int read_action_data(const char *memory, uint32_t buffer_size) {
  //  auto s = context.get_action().data.size();
  //  if( buffer_size == 0 ) return s;
  //
  //  auto copy_size = std::min( static_cast<size_t>(buffer_size), s );
  //  memcpy( (char*)memory.value, context.get_action().data.data(), copy_size
  //  );
  //(uint64_t*)(memory+8)
  //  return copy_size;
  std::vector<uint64_t> data = {7,8};
  memcpy((uint64_t*)memory, data.data(),16);

  return buffer_size;
}

int action_data_size() { return 2*sizeof(uint64_t); }

struct mocked_context {
  //  void print_name(const char* nm) { std::cout << "Name : " << nm << " " <<
  //  field << "\n"; }
  static void *memset(void *ptr, int x, size_t n) {
    return ::memset(ptr, x, n);
  }
  static void *memcpy(void *ptr, const void *x, size_t n) {
    return ::memcpy(ptr, x, n);
  }
};

using backend_t = eosio::vm::backend<mocked_context>;
using rhf_t = eosio::vm::registered_host_functions<mocked_context>;

class eosvm_tester : public testing::Test {
protected:
  void execute_contract(const std::string &path) {

    std::ifstream input(path, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = input.tellg();
    std::vector<char> tmp(pos);
    input.seekg(0, std::ios::beg);
    input.read(&tmp[0], pos);

    std::vector<uint8_t> wasm;

    std::copy(tmp.begin(), tmp.end(), std::back_inserter(wasm));

    /* (import "env" "prints" (func (;0;) (type 0)))
     (import "env" "printui" (func (;1;) (type 1)))
     (import "env" "action_data_size" (func (;2;) (type 2)))
     (import "env" "eosio_assert" (func (;3;) (type 3)))
     (import "env" "memset" (func (;4;) (type 4)))
     (import "env" "read_action_data" (func (;5;) (type 5)))
     (import "env" "memcpy" (func (;6;) (type 4)))
     (import "env" "eosio_assert_code" (func (;7;) (type 6)))*/

    rhf_t::add<nullptr_t, &prints, eosio::vm::wasm_allocator>("env", "prints");
    rhf_t::add<nullptr_t, &printui, eosio::vm::wasm_allocator>("env",
                                                               "printui");
    rhf_t::add<nullptr_t, &action_data_size, eosio::vm::wasm_allocator>(
        "env", "action_data_size");
    rhf_t::add<nullptr_t, &eosio_assert, eosio::vm::wasm_allocator>(
        "env", "eosio_assert");
    rhf_t::add<nullptr_t, &mocked_context::memset,
               eosio::vm::wasm_allocator>("env", "memset");
    rhf_t::add<nullptr_t, &read_action_data, eosio::vm::wasm_allocator>(
        "env", "read_action_data");
    rhf_t::add<nullptr_t, &mocked_context::memcpy,
               eosio::vm::wasm_allocator>("env", "memcpy");
    rhf_t::add<nullptr_t, &eosio_assert_code, eosio::vm::wasm_allocator>(
        "env", "eosio_assert_code");

    backend_t backend(wasm, rhf_t{});
    eosio::vm::wasm_allocator wa;
    eosio::vm::watchdog wd{std::chrono::seconds(3)};
    // Point the backend to the allocator you want it to use.
    backend.set_wasm_allocator(&wa);
    backend.initialize();
    // Resolve the host functions indices.

    // Instaniate a "host"
    mocked_context hm;
    uint64_t a = 3;
    uint64_t b = 4;
    backend(&hm, "env", "apply","test"_n.value, "test"_n.value, "add"_n.value);
  }
};