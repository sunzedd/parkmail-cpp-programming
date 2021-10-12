#include "string_array.h"


void destroy_string_array(char** str_array, int str_count) {
    if (!str_array) {
        return;
    }

    for (int i = 0; i < str_count; ++i) {
        if (str_array[i]) {
            free(str_array[i]);
        }
    }

    free(str_array);
}


char** split_string(int* err, int* str_count,
                    const char* const input_str,
                    const char* const delimeters) {

    if (!str_count || !input_str || !delimeters || strlen(input_str) == 0) {
        *err = ERR_INVALID_ARGS;
        return NULL;
    }

    int token_count = 0;
    const char* curr = input_str;
    const char* last_delimeter = NULL;

    while (*curr) {
        if (strchr(delimeters, *curr)) {
            ++token_count;
            last_delimeter = curr;
        }
        ++curr;
    }

    if (last_delimeter) {
        if (last_delimeter == (input_str + strlen(input_str) - 1)) {
            --token_count;
        }
        else if (last_delimeter < (input_str + strlen(input_str) - 1)) {
            ++token_count;
        }
    } else {
        ++token_count;
    }

    char** result = (char**)malloc(sizeof(char*) * token_count);
    if (!result) {
        *err = ERR_MEM_ALLOC;
        return NULL;
    }

    char* tmp_str = strdup(input_str);
    if (!tmp_str) {
        free(result);
        *err = ERR_MEM_ALLOC;
        return NULL;
    }

    char* token_ptr = tmp_str;
    char* rest_of_str = tmp_str;
    int idx = 0;

    int token_found_count = 0;

    for (token_ptr = strtok_r(tmp_str, delimeters, &rest_of_str);
        token_ptr != NULL;
        token_ptr = strtok_r(NULL, delimeters, &rest_of_str))
    {
        ++token_found_count;

        result[idx] = strdup(token_ptr);
        if (!result[idx]) {
            destroy_string_array(result, token_count);
            *err = ERR_MEM_ALLOC;
            return NULL;
        }

        ++idx;
    }

    if (*err == OK) {
        if (token_found_count == 0) {
            // Случай, если входная строка состоит только из разделителей
            // считаем, что функция отработала верно, но возвращаем NULL
            *str_count = 0;
            destroy_string_array(result, token_count);
            return NULL;
        }
        else {
            *str_count = token_count;
        }
    }

    return result;
}
