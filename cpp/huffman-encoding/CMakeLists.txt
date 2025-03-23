cmake_minimum_required(VERSION 3.30)
project(huffman_encoding)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(run_tests
        tests/test_main.cpp
        tests/test_CharCounter.cpp
        tests/test_HuffmanTree.cpp
)

target_link_libraries(run_tests gtest gtest_main)

add_executable(huffman_encoding src/main.cpp)
