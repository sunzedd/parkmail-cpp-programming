cmake_minimum_required(VERSION 3.16)
project(test_parsetag CXX)

enable_testing()
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-g3)

set(TEST_SOURCES test_main.cpp test_string_array.cpp test_tag.cpp)

add_executable(test ${TEST_SOURCES})
target_include_directories(test PRIVATE ../include/ ${GTEST_INCLUDE_DIRS})
target_link_libraries(test parsetag ${GTEST_LIBRARIES} pthread)
