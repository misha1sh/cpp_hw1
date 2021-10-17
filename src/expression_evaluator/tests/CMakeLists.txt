include(GoogleTest)
enable_testing()

add_executable(
        test_expression_evaluator
        test_expression_evaluator.cpp
)
target_link_libraries(
        test_expression_evaluator
        expressions_evaluator_lib
        gtest_main
)

gtest_discover_tests(test_expression_evaluator)

