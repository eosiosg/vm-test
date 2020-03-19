cmake_minimum_required(VERSION 3.15)
project(vm_test)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(vm)
add_subdirectory(test)
add_subdirectory(secp256k1)

add_executable(main main.cpp)

target_link_libraries(main eos-vm)