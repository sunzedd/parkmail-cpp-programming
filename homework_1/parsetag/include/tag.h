#pragma once

#include "error_codes.h"
#include "string_array.h"

#define TAG_TYPE_OPENING 0
#define TAG_TYPE_CLOSING 1

typedef struct attribute {
    char* name;
    char* value;
} attribute;

typedef struct tag {
    char* name;
    short type;
    int attribute_count;
    attribute* attributes;
} tag;

void attribute_destroy_internals(attribute* attrib);

attribute attribute_construct_from_html(int* err, const char* const html_str);

int tag_validate_html_str(const char* const tag_str);

void tag_destroy(tag* tag);

tag* tag_create_from_html(int* err, const char* const tag_str);
