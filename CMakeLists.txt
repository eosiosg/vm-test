cmake_minimum_required(VERSION 3.15)

add_subdirectory(evmc)

project(vm_test)

set(CMAKE_CXX_STANDARD 17)

if(APPLE AND UNIX AND "${OPENSSL_ROOT_DIR}" STREQUAL "")
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl@1.1")
endif()

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

if(APPLE AND UNIX AND "${JSONCPP_ROOT_DIR}" STREQUAL "")
    set(JSONCPP_ROOT_DIR "/usr/local/opt/jsoncpp")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

if (JSONCPP_FOUND)
    if (APPLE)
        include_directories(${JSONCPP_ROOT_DIR}/include)
        set(JSONCPP_LIBRARIES ${JSONCPP_ROOT_DIR}/lib/libjsoncpp.dylib)
        message(STATUS "JSONCPP Version: ${JSONCPP_VERSION} ${JSONCPP_INCLUDE_DIR} ${JSONCPP_LIBRARIES}")
    else()
        set(JSONCPP_ROOT_DIR /usr/local/opt/jsoncpp)
        include_directories(${JSONCPP_INCLUDE_DIR})
        message(STATUS "JSONCPP Version: ${JSONCPP_VERSION} ${JSONCPP_INCLUDE_DIR} ${JSONCPP_LIBRARIES}")
    endif()
endif()

set(include_dir ${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES $${PROJECT_SOURCE_DIR}/lib/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp)
list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/lib/execution.cpp" "${PROJECT_SOURCE_DIR}/lib/execution.hpp" "${PROJECT_SOURCE_DIR}/lib/eosevm.cpp")

add_subdirectory(lib)

add_subdirectory(vm)
add_subdirectory(test)
add_subdirectory(secp256k1)