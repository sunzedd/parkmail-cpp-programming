#include "mood/mood_determine.h"

#include "worker_process.h"

#include <memory.h>
#include <stddef.h>
#include <sys/sysinfo.h>

mood_error_t mood_determine(const char *str, mood_t *out) {
    if (!str || !out) {
        return ERR_NULLPTR_REFERENCE;
    }

    size_t str_len = strlen(str) + 1;
    size_t worker_count = get_nprocs();
    if (str_len < worker_count) {
        worker_count = 1;
    }

    long long int *shared_output =
            (long long int *)mmap(NULL,
                                  sizeof(long long int) * worker_count,
                                  PROT_READ | PROT_WRITE,
                                  MAP_SHARED | MAP_ANONYMOUS,
                                  -1, 0);
    if (!shared_output) {
        return ERR_SHARED_MEM_BAD_ALLOC;
    }

    dispatch_workers_and_wait(str, str_len, shared_output, worker_count);
    long long int mood_sum = sum_workers_output(shared_output, worker_count);
    *out = mood_determine_from_value(mood_sum);

    munmap(shared_output, sizeof(long long int) * worker_count);
    return ERR_OK;
}
