set(SOURCES src/mood_determine.c)
add_library(mood_mp SHARED ${SOURCES})
target_include_directories(mood_mp PUBLIC include)
target_link_libraries(mood_mp PUBLIC mood_common)

add_subdirectory(tests)
