# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(Pachinko LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directory
include_directories(include)

# ----------------------------
# Create library for the core game
# ----------------------------
add_library(pachinko_lib
        src/peg.cpp
        src/board.cpp
)

target_include_directories(pachinko_lib PUBLIC include)

# ----------------------------
# Main executable
# ----------------------------
add_executable(pachinko
        src/main.cpp
)

target_link_libraries(pachinko pachinko_lib)

# ----------------------------
# Unit tests
# ----------------------------
add_executable(test_pachinko
        tests/test_peg.cpp
        tests/test_board.cpp
)

target_link_libraries(test_pachinko pachinko_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_pachinko)
