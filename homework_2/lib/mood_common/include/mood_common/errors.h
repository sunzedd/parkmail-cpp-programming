#ifndef MOOD_COMMON_ERRORS_H
#define MOOD_COMMON_ERRORS_H

typedef enum {
    ERR_OK = 0,
    ERR_INVALID_ARG = -1,
    ERR_NULLPTR_REFERENCE = -2,
    ERR_BAD_ALLOC = -3,
    ERR_BAD_FILE = -4,
    ERR_EMPTY_FILE = -5,
    ERR_SHARED_MEM_BAD_RELEASE = -6,
    ERR_SHARED_MEM_BAD_ALLOC = -7,
    ERR_PROC_CREATE_FAILURE = -8
} mood_error_t;

#endif
