#ifndef READER_UTILS_READ_FILE_H
#define READER_UTILS_READ_FILE_H

#include "mood_common/errors.h"
#include "mood_common/mood_state.h"
#include <stdio.h>
#include <stdlib.h>

mood_error_t read_file(const char *filepath, char **out_str);

#endif
