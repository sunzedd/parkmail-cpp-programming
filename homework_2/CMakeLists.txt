cmake_minimum_required(VERSION 3.16)

project(homework_2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-g3 -Wall -Werror -pedantic)

add_subdirectory(lib/mood_common)
add_subdirectory(lib/reader_utils)
add_subdirectory(lib/mood)
add_subdirectory(lib/mood_mp)

add_executable(homework_2 examples/main.c)

target_link_libraries(homework_2
                                 mood_mp
                                 reader_utils)
