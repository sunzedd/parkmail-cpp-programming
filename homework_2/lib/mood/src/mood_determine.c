#include "mood/mood_determine.h"
#include <stdbool.h>
#include <stddef.h>

static mood_error_t count_digraphs(const char *const str, size_t *out_score) {
    if (!str || !out_score) {
        return ERR_NULLPTR_REFERENCE;
    }

    *out_score = 0;

    bool met_colon = false;

    for (const char *cur = &str[0]; *cur != '\0'; ++cur) {
        if (*cur == ':') {
            met_colon = true;
        } else {
            if (met_colon) {
                *out_score += get_digraph_mood_value(*cur);
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

    size_t mood_score = 0;

    mood_error_t err = count_digraphs(str, &mood_score);
    if (err == ERR_OK) {
        if (mood_score == 0) {
            *out = NEUTRAL;
        } else if (mood_score > 0) {
            *out = POSITIVE;
        } else {
            *out = NEGATIVE;
        }
    }

    return err;
}
