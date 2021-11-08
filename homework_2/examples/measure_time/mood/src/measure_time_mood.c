#include <mood/mood_determine.h>
#include <reader_utils/read_file.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_REPEAT_COUNT 30

mood_error_t run_test(const char *const input_data_filepath, double *out_cpu_time_ms) {
    char *s = NULL;
    mood_error_t err = read_file(input_data_filepath, &s);
    if (err) {
        return err;
    }

    mood_t mood = MOOD_NEUTRAL;

    clock_t start = clock();
    err = mood_determine(s, &mood);
    clock_t end = clock();

    *out_cpu_time_ms = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    if (s) {
        free(s);
    }

    return err;
}

mood_error_t measure_avg_cpu_time_ms(const char *const input_data_filepath, double *out_avg_cpu_time) {
    double summary_cpu_time = 0;
    double iteration = 0;
    mood_error_t err = ERR_OK;

    for (; iteration < TEST_REPEAT_COUNT && !err; ++iteration) {
        double iteration_cpu_time = 0;
        err = run_test(input_data_filepath, &iteration_cpu_time);
        summary_cpu_time += iteration_cpu_time;
    }

    *out_avg_cpu_time = summary_cpu_time / iteration;
    return err;
}

int main() {
    double avg_time_1mb = 0;
    double avg_time_10mb = 0;
    double avg_time_100mb = 0;
    double avg_time_1gb = 0;

    mood_error_t err_1mb    = measure_avg_cpu_time_ms("data/1mb.txt", &avg_time_1mb);
    mood_error_t err_10mb   = measure_avg_cpu_time_ms("data/10mb.txt", &avg_time_10mb);
    mood_error_t err_100mb  = measure_avg_cpu_time_ms("data/100mb.txt", &avg_time_100mb);
    mood_error_t err_1gb    = measure_avg_cpu_time_ms("data/1gb.txt", &avg_time_1gb);

    printf("Running time test for MOOD lib (single process version)\n");
    printf("measuring average time (%d repeats) ...\n", TEST_REPEAT_COUNT);
    printf("+--------------------------------+\n");
    printf("|    Size   | Status  |   Time (ms)|\n");
    printf("+-----------+---------+----------+\n");
    printf("|    1 Mb   |    %d   |  %f |\n", err_1mb, avg_time_1mb);
    printf("|   10 Mb   |    %d   |  %f |\n", err_10mb, avg_time_10mb);
    printf("|  100 Mb   |    %d   |  %f |\n", err_100mb, avg_time_100mb);
    printf("|    1 Gb   |    %d   |  %f |\n", err_1gb, avg_time_1gb);
    printf("|------------------------------|\n\n");

    return 0;
}
