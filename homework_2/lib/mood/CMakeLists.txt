set(SOURCES src/test_func.c)
add_library(mood STATIC ${SOURCES})
target_include_directories(mood PUBLIC include)
target_link_libraries(mood PUBLIC reader_utils
                           PUBLIC errors)
