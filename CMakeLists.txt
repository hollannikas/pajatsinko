cmake_minimum_required(VERSION 3.16)
project(Pachinko LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

add_library(pachinko src/peg.cpp
        include/board.h
        src/board.cpp)

add_executable(test_pachinko tests/test_peg.cpp
        tests/test_board.cpp
)
target_link_libraries(test_pachinko pachinko GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_pachinko)
