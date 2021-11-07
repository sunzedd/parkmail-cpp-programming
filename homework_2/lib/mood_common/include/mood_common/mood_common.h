#ifndef MOOD_COMMON_MOOD_COMMON_H
#define MOOD_COMMON_MOOD_COMMON_H

#include "mood_common/mood_state.h"

int character_mood_value(char c);
mood_t mood_determine_from_value(long long int mood_value);

#endif
