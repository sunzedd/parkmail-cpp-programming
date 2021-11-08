#include "mood_common/mood_common.h"

int character_mood_value(char c) {
    if (c == ')') {
        return 1;
    }
    if (c == '(') {
        return -1;
    }
    return 0;
}

mood_t mood_determine_from_value(long long int mood_value) {
    if (mood_value == 0) {
        return MOOD_NEUTRAL;
    }
    if (mood_value > 0) {
        return MOOD_POSITIVE;
    }
    return MOOD_NEGATIVE;
}
