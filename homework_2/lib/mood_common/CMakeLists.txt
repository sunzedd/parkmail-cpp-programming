add_library(mood_common src/mood_common.c
                        src/errors.c)
target_include_directories(mood_common PUBLIC include)
