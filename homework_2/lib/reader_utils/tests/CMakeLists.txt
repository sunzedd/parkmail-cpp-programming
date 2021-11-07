project(ReaderUtilsTest CXX)
add_executable(test_reader_utils src/unit/test_reader_utils.cpp)
target_link_libraries(test_reader_utils reader_utils GTest::Main)
add_test(NAME test_reader_utils
        COMMAND test_reader_utils
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
