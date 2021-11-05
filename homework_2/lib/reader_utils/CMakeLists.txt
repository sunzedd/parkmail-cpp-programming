set(SOURCES src/test_func.c)
add_library(reader_utils ${SOURCES})
target_include_directories(reader_utils PUBLIC include)
