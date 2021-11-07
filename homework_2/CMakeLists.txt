cmake_minimum_required(VERSION 3.16)
project(homework_2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-g3 -Wall -Werror -pedantic)

option(BUILD_TESTS "Build tests for all subprojects" ON)
if (BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    find_package(Threads REQUIRED)
endif()

add_subdirectory(lib/mood_common)
add_subdirectory(lib/reader_utils)
add_subdirectory(lib/mood)
add_subdirectory(lib/mood_mp)

add_executable(homework_2 examples/main.c)

option(MOODLIB_MP "Build with parallel version of mood library")
if(MOODLIB_MP)
    set(LIBS mood_mp reader_utils)
else()
    set(LIBS mood reader_utils)
endif()

target_link_libraries(homework_2 ${LIBS})
