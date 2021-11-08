project(MoodTest CXX)

add_executable(stress_mood src/stress_mood.cpp)
target_link_libraries(stress_mood mood reader_utils GTest::Main)
add_test(NAME stress_mood
        COMMAND stress_mood
        )
#WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}

#[[add_executable(stress_mood_mp src/stress_mood_mp.cpp)
target_link_libraries(stress_mood mood_mp reader_utils GTest::Main)
add_test(NAME stress_mood_mp
        COMMAND stress_mod_mp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})]]
