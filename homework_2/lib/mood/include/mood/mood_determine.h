#pragma once
#include <errors/errors.h>

typedef enum {
    POSITIVE,
    NEUTRAL,
    NEGATIVE,
} mood_t;

mood_error_t mood_determine(const char *const str, mood_t *out);
