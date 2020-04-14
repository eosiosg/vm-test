include(LibraryTools)

add_library(eosevm SHARED
        ${include_dir}/eosevm.h
        mocked_context.hpp
        eosevm.cpp
        execution.cpp
        execution.hpp
        base58.cpp
        base58.hpp
        check.hpp
        name.hpp
        cypto.cpp
        cypto.hpp
        serialization.cpp
        serialization.hpp
        contract/challenge_contract.hpp)

target_link_libraries(eosevm PUBLIC evmc::evmc eos-vm OpenSSL::SSL secp256k1 jsoncpp_lib)
target_include_directories(eosevm PUBLIC
        $<BUILD_INTERFACE:${include_dir}>$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

set_target_properties(
        eosevm
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_SOVERSION}
)

if(NOT SANITIZE)
    target_link_options(eosevm PRIVATE $<$<PLATFORM_ID:Linux>:LINKER:--no-undefined>)
endif()

set_source_files_properties(eosevm.cpp PROPERTIES COMPILE_DEFINITIONS PROJECT_VERSION="${PROJECT_VERSION}")

add_standalone_library(eosevm)