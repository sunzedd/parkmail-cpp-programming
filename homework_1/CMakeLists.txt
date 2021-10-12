cmake_minimum_required(VERSION 3.16)
project(homework_1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g3 --coverage -Wall -Werror -pedantic -Wno-unused-result")

set(SOURCE cmd/main.c)

add_subdirectory(parsetag)
add_executable(tag.exec ${SOURCE})
target_include_directories(tag.exec PRIVATE parsetag/include/)
target_link_libraries(tag.exec parsetag)
