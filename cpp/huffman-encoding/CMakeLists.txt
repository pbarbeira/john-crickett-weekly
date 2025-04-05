cmake_minimum_required(VERSION 3.30)
project(huffman_encoding)

set(CMAKE_CXX_STANDARD 23)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests tests/test_main.cpp
        tests/encoder/test_CharCounter.cpp
        tests/encoder/test_HuffmanTree.cpp
        tests/encoder/test_Encoder.cpp
        tests/encoder/test_Decoder.cpp
        tests/utils/test_Writer.cpp
        tests/utils/test_Reader.cpp
        tests/utils/test_ByteConverter.cpp
        tests/utils/test_StringUtils.cpp
        tests/integration/tests_integration.cpp
)

target_link_libraries(run_tests gtest gmock gtest_main)

add_executable(huffman_encoding src/main.cpp
        src/encoder/CharCounter.h
        src/encoder/Encoder.h
        src/encoder/HuffmanTree.h
        src/encoder/Decoder.h
        src/utils/Writer.h
        src/utils/Reader.h
        src/utils/ByteConverter.h
        src/utils/StringUtils.h
        src/HuffmanFactory.h
        src/HuffmanEngine.h
)
