#include "mood/mood_determine.h"
#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct shared_data {
    char *buf;
    size_t size;
    long long int *mood_score;
} shared_data_t;

typedef struct worker_data {
    shared_data_t data;
    struct {
        size_t begin;
        size_t end;
    } region_indices;
} worker_data_t;

static mood_error_t count_digraphs_in_region(const char *buf, size_t buf_size,
                                             size_t region_begin_idx,
                                             size_t region_end_idx,
                                             size_t *out_mood_score) {
    bool met_colon = false;

    const char *cur = &buf[region_begin_idx];
    for (; cur != &buf[region_end_idx]; ++cur) {
        if (*cur == ':') {
            met_colon = true;
        } else {
            if (met_colon) {
                *out_mood_score += get_digraph_mood_value(*cur);
                met_colon = false;
            }
        }
    }

    if (met_colon) {
        if (cur + 1 <= buf + buf_size) {
            ++cur;
            *out_mood_score += get_digraph_mood_value(*cur);
        }
    }

    return ERR_OK;
}

static void run_worker(worker_data_t wd) {
    pid_t pid = fork();
    if (pid == -1) {
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        size_t mood_score = 0;
        count_digraphs_in_region(wd.data.buf, wd.data.size,
                                 wd.region_indices.begin, wd.region_indices.end,
                                 &mood_score);
        // TODO: critical section
        // mutex_lock();
        *(wd.data.mood_score) += mood_score;
        // mutex_unlock();
        // ---
        exit(EXIT_SUCCESS);
    }
}

static void dispatch_workers_and_wait(shared_data_t data, size_t worker_count) {
    assert(worker_count > 1);
    size_t worker_region_size = data.size / worker_count;
    size_t unowned_region_size = data.size - worker_region_size * worker_count;

    size_t region_begin_idx = 0;
    size_t region_end_idx = region_begin_idx + worker_region_size;

    for (int i = 0; i < worker_count - 1; ++i) {
        worker_data_t wd = {.data = data,
                            .region_indices = {.begin = region_begin_idx,
                                               .end = region_end_idx}};

        region_begin_idx += worker_region_size;
        region_end_idx += worker_region_size;

        run_worker(wd);
    }

    if (unowned_region_size > 0) {
        worker_data_t wd = {.data = data,
                            .region_indices = {.begin = region_begin_idx,
                                               .end = region_end_idx}};

        run_worker(wd);
    }

    int worker_status;
    while (wait(&worker_status) > 0);
}

mood_error_t mood_determine(const char *str, mood_t *out) {
    if (!str || !out) {
        return ERR_NULLPTR_REFERENCE;
    }

    size_t shared_buf_size = strlen(str) + 1;
    char *shared_buf =
        (char *)mmap(NULL, shared_buf_size, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (!shared_buf) {
        return ERR_SHARED_MEM_BAD_ALLOC;
    }

    long long int *mood_score = (long long int *)mmap(
        NULL, sizeof(long long int), PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (!mood_score) {
        munmap(shared_buf, shared_buf_size);
        return ERR_SHARED_MEM_BAD_ALLOC;
    }

    memcpy(shared_buf, str, shared_buf_size - 1);
    *mood_score = 0;

    mood_error_t err = ERR_OK;
    size_t worker_count = get_nprocs();
    if (shared_buf_size < worker_count) {
        worker_count = 1;
    }

    shared_data_t worker_data = {
        .buf = shared_buf, .size = shared_buf_size, .mood_score = mood_score};

    dispatch_workers_and_wait(worker_data, worker_count);

    if (*(worker_data.mood_score) == 0) {
        *out = NEUTRAL;
    } else if (*(worker_data.mood_score) > 0) {
        *out = POSITIVE;
    } else {
        *out = NEGATIVE;
    }

    munmap(shared_buf, shared_buf_size);
    munmap(mood_score, sizeof(long long int));
    return err;
}
