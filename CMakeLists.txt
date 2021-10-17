cmake_minimum_required(VERSION 3.17)
project(hw_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(. )
add_subdirectory("${PROJECT_SOURCE_DIR}/deps/googletest" "deps/googletest")


add_subdirectory(src/big_number)
add_subdirectory(src/expression_evaluator)


# main (console application)
add_executable(
        main
        src/main.cpp
)
target_link_libraries(
        main
        big_number_lib
        expressions_evaluator_lib
)


