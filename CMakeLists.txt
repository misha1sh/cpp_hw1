cmake_minimum_required(VERSION 3.20)
project(hw_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/googletest" "deps/googletest")

# big num library
add_library(big_number_lib
    src/big_number.cpp
    src/big_number.h)

# main (console application)
add_executable(
        main
        src/main.cpp
)
target_link_libraries(
        main
        big_number_lib
)

# google tests
enable_testing()

add_executable(
    test_big_number
    src/tests/test_big_number.cpp
)
target_link_libraries(
    test_big_number
    big_number_lib
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_big_number)
