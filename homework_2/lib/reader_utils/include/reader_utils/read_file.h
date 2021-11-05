#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "errors/errors.h"

mood_error_t read_file(const char *const filepath, char **out_str);
