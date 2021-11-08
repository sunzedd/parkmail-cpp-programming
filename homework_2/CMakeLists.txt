cmake_minimum_required(VERSION 3.16)
project(homework_2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-g3 -Wall -Werror -Wpedantic --coverage)
add_link_options(--coverage)

option(BUILD_TESTS "Build tests for all subprojects" ON)
if (BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    find_package(Threads REQUIRED)
endif()

option(MOODLIB_MP "Build examples with parallel version of mood library")
if (MOODLIB_MP)
    set(MOODLIB_MP ON)
endif()

add_subdirectory(lib/mood_common)
add_subdirectory(lib/reader_utils)
add_subdirectory(lib/mood)
add_subdirectory(lib/mood_mp)

add_subdirectory(examples/basic_example_1)
add_subdirectory(examples/measure_time)
