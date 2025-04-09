cmake_minimum_required(VERSION 3.30)
project(cccut)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests test/test_main.cpp
        test/unit_Reader.cpp
        test/unit_Options.cpp
        test/unit_Logger.cpp
        test/unit_Grid.cpp
        test/unit_StringUtils.cpp
)

target_link_libraries(run_tests gtest gmock gtest_main)

add_executable(cccut src/main.cpp
        src/Reader.h
        src/Options.h
        src/Logger.h
        src/Grid.h
        src/StringUtils.h
)
