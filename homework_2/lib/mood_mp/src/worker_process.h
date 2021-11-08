#ifndef MOOD_WORKER_PROCESS_H
#define MOOD_WORKER_PROCESS_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct shared_data {
    char *buf;
    size_t size;
    long long int *workers_output;
} shared_data_t;

typedef struct worker_data {
    unsigned int id;
    shared_data_t shared;
    struct {
        size_t begin;
        size_t end;
    } region_bound_indices;
} worker_data_t;

static void count_mood_value_in_region(const char *buf, size_t buf_size,
                                       size_t region_begin_idx,
                                       size_t region_end_idx,
                                       long long int *out_mood_value) {
    assert(buf);
    assert(out_mood_value);

    bool met_colon = false;

    const char *cur = &buf[region_begin_idx];
    for (; cur != &buf[region_end_idx]; ++cur) {
        if (*cur == ':') {
            met_colon = true;
        } else {
            if (met_colon) {
                *out_mood_value += character_mood_value(*cur);
                met_colon = false;
            }
        }
    }

    if (met_colon) {
        *out_mood_value += character_mood_value(*cur);
    }
}

static void run_worker(worker_data_t wd) {
    pid_t pid = fork();
    if (pid == -1) {
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        long long int region_mood_value = 0;
        count_mood_value_in_region(wd.shared.buf, wd.shared.size,
                                   wd.region_bound_indices.begin,
                                   wd.region_bound_indices.end,
                                   &region_mood_value);
        wd.shared.workers_output[wd.id] = region_mood_value;
        exit(EXIT_SUCCESS);
    }
}

static void dispatch_workers_and_wait(shared_data_t data, size_t worker_count) {
    size_t worker_region_size = data.size / worker_count;
    size_t unowned_region_size = data.size - worker_region_size * worker_count;

    size_t region_begin_idx = 0;
    size_t region_end_idx = region_begin_idx + worker_region_size;

    for (int i = 0; i < worker_count; ++i) {
        worker_data_t wd = {
                .id = i,
                .shared = data,
                .region_bound_indices = { region_begin_idx, region_end_idx }
        };

        region_begin_idx += worker_region_size;
        if (i == worker_count - 2) {
            region_end_idx += worker_region_size + unowned_region_size;
        } else {
            region_end_idx += worker_region_size;
        }

        run_worker(wd);
    }

    int worker_status;
    while (wait(&worker_status) != -1)
    { }
}

static mood_error_t allocate_shared_memory(char **out_buf, size_t buf_size,
                                           long long int **out_workers_output,
                                           size_t worker_count) {
    assert(out_buf && !(*out_buf));
    assert(out_workers_output && !(*out_workers_output));

    *out_buf = (char *)mmap(NULL, buf_size,
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS,
                            -1, 0);
    if (!(*out_buf)) {
        return ERR_SHARED_MEM_BAD_ALLOC;
    }

    *out_workers_output =
            (long long int *)mmap(NULL,
                                  sizeof(long long int) * worker_count,
                                  PROT_READ | PROT_WRITE,
                                  MAP_SHARED | MAP_ANONYMOUS,
                                  -1, 0);
    if (!(*out_workers_output)) {
        munmap(*out_buf, buf_size);
        return ERR_SHARED_MEM_BAD_ALLOC;
    }

    return ERR_OK;
}

static long long int sum_workers_output(const long long int *const workers_output,
                                        size_t worker_count) {
    assert(workers_output);

    long long int result = 0;
    for (int i = 0; i < worker_count; ++i) {
        result += workers_output[i];
    }

    return result;
}

#endif
