# big num library
add_library(expressions_evaluator_lib
        common.h
        evaluator.h
        evaluator.cpp
        operators.h
        operators.cpp
        tokens.h
        tokens_parser.h
        tokens_parser.cpp)

target_include_directories(expressions_evaluator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
        expressions_evaluator_lib
        big_number_lib
)

add_subdirectory(tests)
