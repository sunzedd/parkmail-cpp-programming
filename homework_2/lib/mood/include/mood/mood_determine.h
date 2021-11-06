#ifndef MOOD_MOOD_DETERMINE_H
#define MOOD_MOOD_DETERMINE_H

#include <mood_common/errors.h>
#include <mood_common/mood_state.h>
#include <mood_common/mood_common.h>

mood_error_t mood_determine(const char *str, mood_t *out);

#endif
