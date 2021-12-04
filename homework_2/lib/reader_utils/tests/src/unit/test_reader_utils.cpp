#include <gtest/gtest.h>
#include "stdio.h"

extern "C" {
#include "reader_utils/read_file.h"
}

TEST(READER_UTILS, NORMAL_EXECUTION) {
    mood_error_t expected_error = ERR_OK;

    char *s = NULL;
    mood_error_t actual_error = read_file("data/1.txt", &s);

    EXPECT_EQ(expected_error, actual_error);
    EXPECT_TRUE(s != nullptr);
    EXPECT_EQ(strlen(s), 65);
    if (s) {
        free(s);
    }
}

TEST(READER_UTILS, FILE_DOES_NOT_EXIST) {
    mood_error_t expected_error = ERR_BAD_FILE;

    char *s = NULL;
    mood_error_t actual_error = read_file("data/FileDoesNotExist.txt", &s);

    EXPECT_EQ(expected_error, actual_error);
    EXPECT_TRUE(s == nullptr);
    if (s) {
        free(s);
    }
}

TEST(READER_UTILS, EMPTY_FILE) {
    mood_error_t expected_error = ERR_EMPTY_FILE;

    char *s = NULL;
    mood_error_t actual_error = read_file("data/empty.txt", &s);

    EXPECT_EQ(expected_error, actual_error);
    EXPECT_TRUE(s == nullptr);
    if (s) {
        free(s);
    }
}
