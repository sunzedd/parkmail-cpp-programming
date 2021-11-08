add_executable(basic_example_1 src/main.c)

if(MOODLIB_MP)
    set(LIBS mood_mp reader_utils)
else()
    set(LIBS mood reader_utils)
endif()

target_link_libraries(basic_example_1 ${LIBS})
