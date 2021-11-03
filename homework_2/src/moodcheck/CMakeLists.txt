cmake_minimum_required(VERSION 3.16)
project(homework_2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Werror -pedantic)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_library(moodcheck STATIC ${SOURCES})
target_include_directories(moodcheck PRIVATE ${PROJECT_SOURCE_DIR}/include/)
