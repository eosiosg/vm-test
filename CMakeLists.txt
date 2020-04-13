cmake_minimum_required(VERSION 3.15)
include(cmake/cable/bootstrap.cmake)
include(CableBuildType)
include(CableCompilerSettings)
include(CablePackage)
include(CableToolchains)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

cable_configure_toolchain(DEFAULT cxx17-pic)
cable_set_build_type(DEFAULT Release CONFIGURATION_TYPES Release Debug)

add_subdirectory(evmc)

project(vm_test)

set(CMAKE_CXX_STANDARD 17)

set(OPENSSL_ROOT_DIR /usr/local/Cellar/openssl@1.1/1.1.1d/)
set(OPENSSL_LIBRARIES /usr/local/Cellar/openssl@1.1/1.1.1d/lib)

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

set(VCPKG_ROOT_DIR /Users/vince/vcpkg)
include(${VCPKG_ROOT_DIR}/scripts/buildsystems/vcpkg.cmake)
find_package(jsoncpp CONFIG REQUIRED)

add_subdirectory(vm)
add_subdirectory(test)
add_subdirectory(secp256k1)

set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(lib)

add_executable(main main.cpp)

target_link_libraries(main eos-vm)