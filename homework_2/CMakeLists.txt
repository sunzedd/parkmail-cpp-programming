cmake_minimum_required(VERSION 3.16)
project(homework_2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-g3 -Wall -Werror -Wpedantic -Wno-unknown-pragmas
                    -Wno-unused --coverage)

add_link_options(--coverage)

enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

option(MOODLIB_MP "Build examples with parallel version of mood library")

add_subdirectory(lib/mood_common)
add_subdirectory(lib/reader_utils)
add_subdirectory(lib/mood)
add_subdirectory(lib/mood_mp)
add_subdirectory(tests/stress)
