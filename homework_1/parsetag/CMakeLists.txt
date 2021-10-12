cmake_minimum_required(VERSION 3.16)
project(parsetag C)

set(CMAKE_C_FLAGS "-g3 --coverage -Wall -Werror -pedantic -Wno-unused-result")
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_library(parsetag STATIC ${SOURCES})
target_include_directories(parsetag PRIVATE include/)
