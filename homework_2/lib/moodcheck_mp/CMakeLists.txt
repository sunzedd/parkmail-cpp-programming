set(SOURCES src/test_func.c)
add_library(moodcheck_mp SHARED ${SOURCES})
target_include_directories(moodcheck_mp PUBLIC include)
target_link_libraries(moodcheck_mp PUBLIC reader_utils)