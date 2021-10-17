
include(GoogleTest)
enable_testing()

add_executable(
        test_big_number
        test_big_number.cpp
)
target_link_libraries(
        test_big_number
        big_number_lib
        gtest_main
)

gtest_discover_tests(test_big_number)
