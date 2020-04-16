cmake_minimum_required(VERSION 3.15)

add_subdirectory(evmc)

project(vm_test)

set(CMAKE_CXX_STANDARD 17)

set(OPENSSL_ROOT_DIR /usr/local/Cellar/openssl@1.1/1.1.1d/)
set(OPENSSL_LIBRARIES ${OPENSSL_LIBRARIES}/lib)

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    if(APPLE)
        include_directories(${OPENSSL_ROOT_DIR}/include)
        list(APPEND LIB_LIST ${OPENSSL_LIBRARIES}/libssl.dylib)
        list(APPEND LIB_LIST ${OPENSSL_LIBRARIES}/libcrypto.dylib)
        message(STATUS "OpenSSL Version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
    else()
        include_directories(${OPENSSL_INCLUDE_DIR})
        list(APPEND LIB_LIST ${OPENSSL_LIBRARIES})
        message(STATUS "OpenSSL Version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
    endif()
endif()


find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
set(JSONCPP_ROOT_DIR /usr/local/Cellar/jsoncpp/1.9.1)
set(JSONCPP_LIBRARIES ${JSONCPP_ROOT_DIR}/lib/libjsoncpp.dylib)
set(JSONCPP_INCLUDE_DIR ${JSONCPP_ROOT_DIR}/include)
include_directories(${JSONCPP_INCLUDE_DIR})


set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(lib)

add_subdirectory(vm)
add_subdirectory(test)
add_subdirectory(secp256k1)


