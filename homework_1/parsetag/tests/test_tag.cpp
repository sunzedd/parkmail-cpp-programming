#include <gtest/gtest.h>

extern "C" {
#include "tag.h"
}

TEST(ATTRIBUTE_CONSTRUCT_FROM_HTML, ATTRIBUTE_HAS_VALUE) {
    // Arrange
    int err = OK;
    const char *const html = "source=\"somepic.jpg\"";

    // Act
    attribute_t a = attribute_construct_from_html(&err, html);

    // Assert
    EXPECT_EQ(err, OK);
    EXPECT_TRUE(a.name != NULL);
    EXPECT_TRUE(a.value != NULL);
    EXPECT_STREQ(a.name, "source");
    EXPECT_STREQ(a.value, "somepic.jpg");

    attribute_destroy_internals(&a);
}

TEST(ATTRIBUTE_CONSTRUCT_FROM_HTML, ATTRIBUTE_HAS_NO_VALUE) {
    // Arrange
    int err = OK;
    const char *const html = "hidden";

    // Act
    attribute_t a = attribute_construct_from_html(&err, html);

    // Assert
    EXPECT_EQ(err, OK);
    EXPECT_TRUE(a.name != NULL);
    EXPECT_TRUE(a.value == NULL);
    EXPECT_STREQ(a.name, "hidden");

    attribute_destroy_internals(&a);
}

TEST(TAG_VALIDATE_HTML_STR, VALID_HTML) {
    // Arrange
    const char *const tag = "<br>";

    // Act
    int err = tag_validate_html_str(tag);

    // Assert
    EXPECT_EQ(err, OK);
}

TEST(TAG_VALIDATE_HTML_STR, INVALID_HTML) {
    // Arrange
    const char *const tag = "<br?";

    // Act
    int err = tag_validate_html_str(tag);

    // Assert
    EXPECT_EQ(err, ERR_INVALID_HTML_SYNTAX);
}

TEST(TAG_CREATE_FROM_HTML, VALID_TAG_OPENING) {
    // Arrange
    int err = OK;
    const char *const html = "<br>";

    // Act
    tag_t *tag = tag_create_from_html(&err, html);

    // Assert
    EXPECT_TRUE(tag != NULL);
    EXPECT_TRUE(tag->name != NULL);
    EXPECT_STREQ(tag->name, "br");
    EXPECT_EQ(tag->type, TAG_TYPE_OPENING);

    tag_destroy(&tag);
}

TEST(TAG_CREATE_FROM_HTML, VALID_TAG_CLOSING) {
    // Arrange
    int err = OK;
    const char *const html = "</br>";

    // Act
    tag_t *tag = tag_create_from_html(&err, html);

    // Assert
    EXPECT_TRUE(tag != NULL);
    EXPECT_TRUE(tag->name != NULL);
    EXPECT_STREQ(tag->name, "br");
    EXPECT_EQ(tag->type, TAG_TYPE_CLOSING);

    tag_destroy(&tag);
}

TEST(TAG_CREATE_FROM_HTML, VALID_TAG_NO_ATTRIBUTES) {
    // Arrange
    int err = OK;
    const char *const html = "<br>";

    // Act
    tag_t *tag = tag_create_from_html(&err, html);

    // Assert
    EXPECT_TRUE(tag != NULL);
    EXPECT_TRUE(tag->name != NULL);
    EXPECT_STREQ(tag->name, "br");
    EXPECT_EQ(tag->attribute_count, 0);
    EXPECT_TRUE(tag->attributes == NULL);

    tag_destroy(&tag);
}

TEST(TAG_CREATE_FROM_HTML, VALID_TAG_MULTIPLE_ATTRIBUTES) {
    // Arrange
    int err = OK;
    const char *const html =
        "<img source=\"somepic.jpg\" width=\"800\" height=\"600\">";

    // Act
    tag_t *tag = tag_create_from_html(&err, html);

    // Assert
    EXPECT_TRUE(tag != NULL);
    EXPECT_TRUE(tag->name != NULL);
    EXPECT_STREQ(tag->name, "img");
    EXPECT_EQ(tag->attribute_count, 3);
    EXPECT_TRUE(tag->attributes != NULL);

    EXPECT_STREQ(tag->attributes[0].name, "source");
    EXPECT_STREQ(tag->attributes[0].value, "somepic.jpg");

    EXPECT_STREQ(tag->attributes[1].name, "width");
    EXPECT_STREQ(tag->attributes[1].value, "800");

    EXPECT_STREQ(tag->attributes[2].name, "height");
    EXPECT_STREQ(tag->attributes[2].value, "600");

    tag_destroy(&tag);
}
