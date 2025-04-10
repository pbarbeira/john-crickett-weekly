cmake_minimum_required(VERSION 3.30)
project(05_load_balancer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(TEST_LIBS gtest gmock gtest_main)
FetchContent_MakeAvailable(googletest)

add_executable(run_all test/test_main.cpp
        test/unit_Logger.cpp
        test/unit_Server.cpp
)

add_executable(run_unit_logger test/test_main.cpp test/unit_Logger.cpp)
add_executable(run_unit_server test/test_main.cpp test/unit_Server.cpp)

target_link_libraries(run_all ${TEST_LIBS})
target_link_libraries(run_unit_logger ${TEST_LIBS})

add_executable(be src/be/main.cpp
        src/lib/Logger.h
        src/Server.h
)

add_executable(lb src/lb/main.cpp
        src/lib/Logger.h
        src/Server.h
        src/Client.h
)
