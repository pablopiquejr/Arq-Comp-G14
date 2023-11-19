cmake_minimum_required(VERSION 3.22)
project(fluid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -O3")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL"
        GIT_TAG v4.0.0
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(GSL)

set(TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(TEST_SOURCES
        ${TEST_SOURCE_DIR}/progargs_test.cpp
        block_test.cpp
        grid_test.cpp
)

add_executable(utest ${TEST_SOURCES})

target_include_directories(utest PRIVATE ${TEST_SOURCE_DIR})
target_link_libraries(utest PRIVATE
        gtest_main
        GSL
        )
include(GoogleTest)
gtest_discover_tests(utest)