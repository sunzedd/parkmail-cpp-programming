#include <gtest/gtest.h>

extern "C" {
#include "mood/mood_determine.h"
}

TEST(MOOD_DETERMINE, EMPTY_INPUT_STRING) {
    const char *const s = "\0";
    mood_t expected_result = MOOD_NEUTRAL;
    mood_error_t expected_error = ERR_OK;

    mood_t actual_result;
    mood_error_t actual_error = mood_determine(s, &actual_result);

    EXPECT_EQ(expected_error, actual_error);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(MOOD_DETERMINE, NULLPTR_STRING) {
    const char *const s = NULL;
    mood_t expected_result = (mood_t)3045123;       // случайное число для проверки,
    // что вызванная функция не изменит значения аргумента,
    // т.к. ожидается, что в функции произойдет ошибка
    mood_error_t expected_error = ERR_NULLPTR_REFERENCE;

    mood_t actual_result = (mood_t)3045123;
    mood_error_t actual_error = mood_determine(s, &actual_result);

    EXPECT_EQ(expected_error, actual_error);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(MOOD_DETERMINE, NO_DIGRAPHS_IN_STRING) {
    const char *const s = "There is no any positive or negative digraphs at all\0";
    mood_t expected_result = MOOD_NEUTRAL;
    mood_error_t expected_error = ERR_OK;

    mood_t actual_result = MOOD_NEGATIVE;
    mood_error_t actual_error = mood_determine(s, &actual_result);

    EXPECT_EQ(expected_error, actual_error);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(MOOD_DETERMINE, NORMAL_EXECUTION_POSITIVE) {
    const char *const s = ":0 There is some positive :) :)))) but sometimes sad too :(\0";
    mood_t expected_result = MOOD_POSITIVE;
    mood_error_t expected_error = ERR_OK;

    mood_t actual_result = MOOD_NEGATIVE;
    mood_error_t actual_error = mood_determine(s, &actual_result);

    EXPECT_EQ(expected_error, actual_error);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(MOOD_DETERMINE, NORMAL_EXECUTION_NEUTRAL) {
    const char *const s = ":) There is some positive :) :( but sometimes sad too :(\0";
    mood_t expected_result = MOOD_NEUTRAL;
    mood_error_t expected_error = ERR_OK;

    mood_t actual_result = MOOD_NEGATIVE;
    mood_error_t actual_error = mood_determine(s, &actual_result);

    EXPECT_EQ(expected_error, actual_error);
    EXPECT_EQ(expected_result, actual_result);
}

TEST(MOOD_DETERMINE, NORMAL_EXECUTION_NEGATIVE) {
    const char *const s = ":( There is some positive :) :( but all day today is sad  :(\0";
    mood_t expected_result = MOOD_NEGATIVE;
    mood_error_t expected_error = ERR_OK;

    mood_t actual_result = MOOD_NEGATIVE;
    mood_error_t actual_error = mood_determine(s, &actual_result);

    EXPECT_EQ(expected_error, actual_error);
    EXPECT_EQ(expected_result, actual_result);
}
