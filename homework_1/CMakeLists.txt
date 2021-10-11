cmake_minimum_required(VERSION 3.16)

project(homework_1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Werror -Wall -g3")

add_executable(app src/main.c)
