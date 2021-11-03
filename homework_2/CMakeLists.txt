cmake_minimum_required(VERSION 3.16)
project(homework_2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-g3 -Wall -Werror -pedantic -Wno-unused-result")

set(SOURCE main.c)
add_executable(homework_2 ${SOURCE})

add_subdirectory(src/moodcheck/)
target_include_directories(homework_2 PRIVATE src/moodcheck/include/)
target_link_libraries(homework_2 moodcheck)
