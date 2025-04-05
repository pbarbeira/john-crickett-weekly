cmake_minimum_required(VERSION 3.30)
project(ccwc)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests test/test_main.cpp
    test/unit_reader.cpp
    test/unit_options.cpp
    test/unit_scanner.cpp
)

target_link_libraries(run_tests gtest gmock gtest_main)

add_executable(wc_tool src/main.cpp
    src/Reader.h
    src/Options.h
    src/Scanner.h
)
