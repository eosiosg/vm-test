enable_testing()

include(GoogleTest)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)


file(COPY ../lib/contract DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

add_executable(HelloTest hello_test.cpp)
target_link_libraries(HelloTest gtest_main eos-vm)

gtest_add_tests(
        TARGET HelloTest
)

add_executable(VMTest vm_test.cpp)
target_link_libraries(VMTest gtest_main eos-vm)

add_executable(TokenTest eosio_token_test.cpp)
target_link_libraries(TokenTest gtest_main eos-vm)

add_executable(ChallengeTest challenge_test.cpp ../lib/serialization.cpp ../lib/other_fc.cpp ../lib/base58.cpp)
target_link_libraries(ChallengeTest gtest_main eos-vm OpenSSL::SSL secp256k1 jsoncpp_lib)


add_executable(MultiIndexTest multi_index_test.cpp)
target_link_libraries(MultiIndexTest gtest_main eos-vm secp256k1)
gtest_add_tests(
        TARGET VMTest
)

#add_test(
#        NAME EosVMTest
#        COMMAND
#)