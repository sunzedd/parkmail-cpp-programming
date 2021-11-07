project(MoodTest CXX)
add_executable(mood_test src/unit/test_mood_determine.cpp)
target_link_libraries(mood_test mood GTest::Main)
add_test(NAME mood_test COMMAND mood_test)
