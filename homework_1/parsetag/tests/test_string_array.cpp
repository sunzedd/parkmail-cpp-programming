#include <gtest/gtest.h>

extern "C" {
#include "string_array.h"
}

TEST(SPLIT_STRING, EMPTY_INPUT_STRING) {
    // Arrange
    const char* const input_str = "";
    int err = 0;
    int str_count = 0;
    const char* const delimeters = "<>/,";

    // Act
    char** str_array = split_string(&err, &str_count, input_str, delimeters);

    // Assert
    EXPECT_EQ(str_count, 0);
    EXPECT_TRUE(str_array == NULL);
    EXPECT_EQ(err, ERR_INVALID_ARGS);

    destroy_string_array(str_array, str_count);
}

TEST(SPLIT_STRING, NO_DELIMETERS_IN_INPUT_STRING) {
    // Arrange
    const char* const input_str = "hello world";
    int err = 0;
    int str_count = 0;
    const char* const delimeters = "<>/,";

    // Act
    char** str_array = split_string(&err, &str_count, input_str, delimeters);

    // Assert
    EXPECT_EQ(str_count, 1);
    EXPECT_TRUE(str_array != NULL);
    EXPECT_EQ(err, OK);
    EXPECT_STREQ(str_array[0], input_str);

    destroy_string_array(str_array, str_count);
}

TEST(SPLIT_STRING, INPUT_STRING_CONTAIN_ONLY_DELIMETERS) {
    // Arrange
    const char* const input_str = "<<<<>>>>//,,,<<,>";
    int err = 0;
    int str_count = 0;
    const char* const delimeters = "<>/,";

    // Act
    char** str_array = split_string(&err, &str_count, input_str, delimeters);

    // Assert
    EXPECT_EQ(str_count, 0);
    EXPECT_TRUE(str_array == NULL);
    EXPECT_EQ(err, OK);
}

TEST(SPLIT_STRING, MULTIPLE_TOKENS) {
    // Arrange
    const char* const input_str = "<img source=\"somepic.jpg\" width=\"800\" height=\"600\">";
    int err = 0;
    int str_count = 0;
    const char* const delimeters = " <>";

    // Act
    char** str_array = split_string(&err, &str_count, input_str, delimeters);

    // Assert
    EXPECT_EQ(str_count, 4);
    EXPECT_TRUE(str_array != NULL);
    EXPECT_STREQ(str_array[0], "img");
    EXPECT_STREQ(str_array[1], "source=\"somepic.jpg\"");
    EXPECT_STREQ(str_array[2], "width=\"800\"");
    EXPECT_STREQ(str_array[3], "height=\"600\"");
    EXPECT_EQ(err, OK);

    destroy_string_array(str_array, str_count);
}

TEST(SPLIT_STRING, SINGLE_TOKEN) {
    // Arrange
    const char* const input_str = "<br>";
    int err = 0;
    int str_count = 0;
    const char* const delimeters = " <>";

    // Act
    char** str_array = split_string(&err, &str_count, input_str, delimeters);

    // Assert
    EXPECT_EQ(str_count, 1);
    EXPECT_TRUE(str_array != NULL);
    EXPECT_STREQ(str_array[0], "br");
    EXPECT_EQ(err, OK);

    destroy_string_array(str_array, str_count);
}
