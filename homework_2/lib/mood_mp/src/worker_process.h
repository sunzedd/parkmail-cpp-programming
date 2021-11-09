#ifndef MOOD_WORKER_PROCESS_H
#define MOOD_WORKER_PROCESS_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct worker_data {
    unsigned int id;
    const char *input_data;
    struct {
        size_t begin;
        size_t end;
    } region_bound_indices;
    long long int *shared_output;
} worker_data_t;

static void count_mood_value_in_region(const char *data,
                                       size_t region_begin_idx,
                                       size_t region_end_idx,
                                       long long int *out_mood_value) {
    assert(data);
    assert(out_mood_value);

    bool met_colon = false;

    const char *cur = &data[region_begin_idx];
    for (; cur != &data[region_end_idx]; ++cur) {
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

static void run_worker(const worker_data_t *const wd) {
    pid_t pid = fork();
    if (pid == -1) {
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        long long int region_mood_value = 0;
        count_mood_value_in_region(wd->input_data,
                                   wd->region_bound_indices.begin,
                                   wd->region_bound_indices.end,
                                   &region_mood_value);
        wd->shared_output[wd->id] = region_mood_value;

        exit(EXIT_SUCCESS);
    }
}

static void dispatch_workers_and_wait(const char *input_data,
                                      size_t data_size,
                                      long long int *shared_output,
                                      size_t worker_count) {
    size_t worker_region_size = data_size / worker_count;
    size_t unowned_region_size = data_size - worker_region_size * worker_count;

    size_t region_begin_idx = 0;
    size_t region_end_idx = region_begin_idx + worker_region_size;

    for (int i = 0; i < worker_count; ++i) {
        worker_data_t wd = {
                .id = i,
                .input_data = input_data,
                .region_bound_indices = { region_begin_idx, region_end_idx },
                .shared_output = shared_output
        };

        region_begin_idx += worker_region_size;
        if (i == worker_count - 2) {
            region_end_idx += worker_region_size + unowned_region_size;
        } else {
            region_end_idx += worker_region_size;
        }

        run_worker(&wd);
    }

    int worker_status;
    while (wait(&worker_status) != -1)
    { }
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
