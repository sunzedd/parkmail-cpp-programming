#include "mood/mood_determine.h"
#include <stdbool.h>
#include <stddef.h>

static mood_error_t count_mood_value(const char *const str,
                                     long long int *out_mood_value) {
    if (!str || !out_mood_value) {
        return ERR_NULLPTR_REFERENCE;
    }

    *out_mood_value = 0;

    bool met_colon = false;

    for (const char *cur = &str[0]; *cur != '\0'; ++cur) {
        if (*cur == ':') {
            met_colon = true;
        } else {
            if (met_colon) {
                *out_mood_value += character_mood_value(*cur);
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

    long long int mood_value = 0;

    mood_error_t err = count_mood_value(str, &mood_value);
    if (err == ERR_OK) {
        if (mood_value == 0) {
            *out = MOOD_NEUTRAL;
        } else if (mood_value > 0) {
            *out = MOOD_POSITIVE;
        } else {
            *out = MOOD_NEGATIVE;
        }
    }

    return err;
}
