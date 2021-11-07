#include "mood/mood_determine.h"

#include "worker_process.h"

#include <memory.h>
#include <stddef.h>
#include <sys/sysinfo.h>

mood_error_t mood_determine(const char *str, mood_t *out) {
    if (!str || !out) {
        return ERR_NULLPTR_REFERENCE;
    }

    size_t shared_buf_size = strlen(str) + 1;
    size_t worker_count = get_nprocs();
    if (shared_buf_size < worker_count) {
        worker_count = 1;
    }
    char *shared_buf = NULL;
    long long int *workers_output = NULL;

    mood_error_t err = allocate_shared_memory(&shared_buf, shared_buf_size,
                                              &workers_output, worker_count);
    if (err != ERR_OK) {
        return err;
    }

    memcpy(shared_buf, str, shared_buf_size - 1);

    shared_data_t worker_shared_data = {
        .buf = shared_buf,
        .size = shared_buf_size,
        .workers_output = workers_output
    };

    dispatch_workers_and_wait(worker_shared_data, worker_count);
    long long int mood_sum = sum_workers_output(workers_output, worker_count);
    *out = mood_determine_from_value(mood_sum);

    munmap(shared_buf, shared_buf_size);
    munmap(workers_output, sizeof(long long int) * worker_count);
    return err;
}
