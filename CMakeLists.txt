cmake_minimum_required(VERSION 3.28)
project(MonteCarloOptionPricing CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic -O2)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(option_pricer ${SOURCES})

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.4
)
FetchContent_MakeAvailable(Catch2)

file(GLOB TEST_SOURCES tests/test_*.cpp)

add_executable(tests ${TEST_SOURCES} ${SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE include)

include(CTest)
include(Catch)
catch_discover_tests(tests)