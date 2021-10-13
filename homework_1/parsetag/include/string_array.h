#pragma once
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"

void destroy_string_array(char **str_array, int str_count);

char **split_string(int *err, int *str_count, const char *const input_str,
                    const char *const delimeters);
