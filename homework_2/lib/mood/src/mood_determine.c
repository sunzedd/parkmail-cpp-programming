#include <stdbool.h>
#include <stddef.h>
#include "mood/mood_determine.h"

static mood_error_t count_digraphs(const char *const str,
                                   size_t *out_positive_count,
                                   size_t *out_negative_count) {
    if (!str || !out_positive_count || !out_negative_count) {
        return ERR_NULLPTR_REFERENCE;
    }

    *out_negative_count = 0;
    *out_positive_count = 0;

    bool met_colon = false;

    for (const char *cur = &str[0]; *cur != '\0'; ++cur) {
        if (*cur == ':') {
            met_colon = true;
        }
        else {
            if (met_colon) {
                if (*cur == ')') {
                    ++(*out_positive_count);
                } else if (*cur == '(') {
                    ++(*out_negative_count);
                }
                met_colon = false;
            }
        }
    }

    return ERR_OK;
}

mood_error_t mood_determine(const char *const str, mood_t *out) {
    if (!str || !out) {
        return ERR_NULLPTR_REFERENCE;
    }

    size_t positive_count = 0;
    size_t negative_count = 0;

    mood_error_t err = count_digraphs(str, &positive_count, &negative_count);
    if (err == ERR_OK) {
        if (positive_count == negative_count) {
            *out = NEUTRAL;
        } else if (positive_count > negative_count) {
            *out = POSITIVE;
        } else {
            *out = NEGATIVE;
        }
    }

    return err;
}
