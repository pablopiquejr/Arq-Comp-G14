# Indicate where to find the source code.
set(TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# List of all test files.
set(TEST_SOURCES
        ${TEST_SOURCE_DIR}/block_test.cpp
        ${TEST_SOURCE_DIR}/grid_test.cpp

)

# Executable for all unit tests with list of sources.
add_executable(utest ${TEST_SOURCES})

# Include directories for the test executable.
target_include_directories(utest PRIVATE ${TEST_SOURCE_DIR})

# Library dependencies.
target_link_libraries(utest PRIVATE sim GTest::gtest_main Microsoft.GSL::GSL)

# Discover all tests and add them to the test driver.
include(GoogleTest)
gtest_discover_tests(utest)