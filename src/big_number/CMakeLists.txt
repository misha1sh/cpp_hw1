# big num library
add_library(big_number_lib
        big_number.cpp
        big_number.h
        common.h
        operations/operations.h
        operations/sum.cpp
        operations/sub.cpp
        operations/mul.cpp
        operations/div.cpp
        operations/compare.cpp
        operations/trim.cpp)

target_include_directories(big_number_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
