#include "string_array.h"

void destroy_string_array(char ***str_array, int str_count) {
    if (!str_array) {
        return;
    }
    if (!(*str_array)) {
        return;
    }

    char **str_array_tmp = *(str_array);

    for (int i = 0; i < str_count; ++i) {
        if ( str_array_tmp[i] ) {
            free( str_array_tmp[i] );
        }
    }

    free(*str_array);
    *str_array = NULL;
}

char **split_string(int *err, int *str_array_size,
                    const char *const delimeters,
                    const char *const str) {

    if (!str_array_size || !str || !delimeters) {
        *err = ERR_INVALID_ARGS;
        return NULL;
    }
    if (strlen(str) == 0) {
        *err = OK;
        return NULL;
    }

    char **result = (char **)calloc(STR_ARRAY_DEFAULT_SIZE, sizeof(char*));
    if (!result) {
        *err = ERR_MEM_ALLOC;
        return NULL;
    }

    char* tmp_str = strdup(str);
    if (!tmp_str) {
        free(result);
        *err = ERR_MEM_ALLOC;
        return NULL;
    }

    char* token = tmp_str;
    char* rest = NULL;
    int idx = 0;
    int actual_array_size = STR_ARRAY_DEFAULT_SIZE;
    int required_array_size = 0;

    for (token = strtok_r(tmp_str, delimeters, &rest);
         token != NULL && *err == OK;
         token = strtok_r(NULL, delimeters, &rest)) {

        if (idx > actual_array_size - 1) {
            required_array_size = actual_array_size * REALLOC_COEF;
            char **tmp_result = realloc(result, required_array_size);
            if (tmp_result) {
                result = tmp_result;
                tmp_result = NULL;
                actual_array_size = required_array_size;
            } else {
                *err = ERR_MEM_ALLOC;
            }
        }

        result[idx] = strdup(token);
        if (!result[idx]) {
            *err = ERR_MEM_ALLOC;
        }

        ++idx;
    }

    required_array_size = idx;

    if (required_array_size == 0) {
        // в строке нет токенов (только разделители)
        destroy_string_array(&result, actual_array_size);
        actual_array_size = 0;
    }

    if (required_array_size < actual_array_size) {
        char **tmp_result = realloc(result, required_array_size);
        if (tmp_result) {
            result = tmp_result;
            tmp_result = NULL;
            actual_array_size = required_array_size;
        }
    }

    if (*err != OK) {
        destroy_string_array(&result, actual_array_size);
        actual_array_size = 0;
    }

    *str_array_size = actual_array_size;

    free(tmp_str);
    return result;
}
