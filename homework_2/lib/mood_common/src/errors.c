#include "mood_common/errors.h"
#include <stdio.h>

void get_error_string(mood_error_t error, char *out) {
    if (!out) {
        return;
    }
    
    switch(error) {
    case (ERR_OK):
        sprintf(out, "OK");
        break;
    case (ERR_INVALID_ARG):
        sprintf(out, "invalid argument");
        break;
    case (ERR_NULLPTR_REFERENCE):
        sprintf(out, "usage of NULL-pointer");
        break;
    case (ERR_BAD_ALLOC):
        sprintf(out, "failed to allocate heap memory");
        break;
    case (ERR_BAD_FILE):
        sprintf(out, "file does not exists");
        break;
    case (ERR_EMPTY_FILE):
        sprintf(out, "file is empty");
        break;
    case (ERR_SHARED_MEM_BAD_RELEASE):
        sprintf(out, "failed to release shared memory block");
        break;
    case (ERR_SHARED_MEM_BAD_ALLOC):
        sprintf(out, "failed to allocate shared memory block");
        break;
    case (ERR_PROC_CREATE_FAILURE):
        sprintf(out, "failed to fork child process");
        break;
    default:
        sprintf(out, "unknown error");
        break;
    }
}
