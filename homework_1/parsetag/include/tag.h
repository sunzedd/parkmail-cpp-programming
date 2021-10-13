#pragma once

#include "error_codes.h"
#include "string_array.h"

#define TAG_TYPE_OPENING 0
#define TAG_TYPE_CLOSING 1

typedef struct attribute_t {
    char *name;
    char *value;
} attribute_t;

typedef struct tag {
    char *name;
    short type;
    int attribute_count;
    attribute_t *attributes;
} tag_t;

void attribute_destroy_internals(attribute_t *attrib);

attribute_t attribute_construct_from_html(int *err, const char *const html_str);

int tag_validate_html_str(const char *const tag_str);

void tag_destroy(tag_t *tag);

tag_t *tag_create_from_html(int *err, const char *const tag_str);
