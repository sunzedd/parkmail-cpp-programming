#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "mood_common/mood_state.h"
#include "mood_common/errors.h"

mood_error_t read_file(const char *const filepath, char **out_str);
