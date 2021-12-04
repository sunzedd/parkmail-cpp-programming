project(MoodTest CXX)
add_executable(test_mood_mp src/unit/test_mood_determine.cpp)
target_link_libraries(test_mood_mp mood_mp GTest::Main)
add_test(NAME test_mood_mp COMMAND test_mood_mp)
