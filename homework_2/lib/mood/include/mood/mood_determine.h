#pragma once
#include <mood_common/errors.h>
#include <mood_common/mood_state.h>

mood_error_t mood_determine(const char *const str, mood_t *out);
