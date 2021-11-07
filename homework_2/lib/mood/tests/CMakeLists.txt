project(MoodTest CXX)
add_executable(test_mood src/unit/test_mood_determine.cpp)
target_link_libraries(test_mood mood GTest::Main)
add_test(NAME test_mood COMMAND test_mood)
