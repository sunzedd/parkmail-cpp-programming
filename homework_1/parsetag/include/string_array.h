#pragma once
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"

#define STR_ARRAY_DEFAULT_SIZE 4
#define REALLOC_COEF 2

void destroy_string_array(char ***str_array, int str_count);

char **split_string(int *err, int *str_array_size, const char *const delimeters, const char *const str);
