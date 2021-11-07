set(SOURCES src/read_file.c)
add_library(reader_utils ${SOURCES})
target_include_directories(reader_utils PUBLIC include)
target_link_libraries(reader_utils PUBLIC mood_common)

add_subdirectory(tests)
