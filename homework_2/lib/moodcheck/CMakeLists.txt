set(SOURCES src/test_func.c)
add_library(moodcheck STATIC ${SOURCES})
target_include_directories(moodcheck PUBLIC include)
target_link_libraries(moodcheck PUBLIC reader_utils)
