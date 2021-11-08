add_executable(measure_time_mood src/measure_time_mood.c)
target_link_libraries(measure_time_mood mood reader_utils)

add_executable(simple_test_mood src/simple_test.c)
target_link_libraries(simple_test_mood mood reader_utils)
