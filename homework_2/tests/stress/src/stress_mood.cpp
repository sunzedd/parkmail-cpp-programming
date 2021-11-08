#include <gtest/gtest.h>
#include <ctime>
#include <vector>
#include <string>

extern "C" {
#include <mood/mood_determine.h>
#include <reader_utils/read_file.h>
}

#define ROUNDS 10

class StressTester : public ::testing::Test {
public:
    static void TearDownTestSuite() {
        std::cout << "\n\n----------------- Time Results ------------------\n";
        for (const auto &s : s_OutputReport) {
            std::cout << s << std::endl;
        }
        std::cout << "------------------------------------------------\n\n";
    }

    static void UpdateReport(int fileSize, double avgCpuTimeMs) {
        std::string s = "File size (Mb): " + std::to_string(fileSize) +
                        "\t Time (ms): " + std::to_string(avgCpuTimeMs);
        s_OutputReport.push_back(s);
    }


    static std::vector<std::string> s_OutputReport;
};

std::vector<std::string> StressTester::s_OutputReport;


static mood_error_t run(const char *s, double *out_cpu_time_ms) {
    mood_t mood = MOOD_NEUTRAL;

    clock_t start = clock();
    mood_error_t err = mood_determine(s, &mood);
    clock_t end = clock();

    *out_cpu_time_ms = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    return err;
}

static void measure_average(const char *s, double *out_avg_cpu_time_ms) {
    long double summary_cpu_time = 0;

    for (int i = 0; i < ROUNDS; ++i) {
        double cpu_time = 0;
        mood_error_t err = run(s, &cpu_time);
        ASSERT_EQ(err, ERR_OK);
        summary_cpu_time += cpu_time;
    }

    *out_avg_cpu_time_ms = (double)(summary_cpu_time / (long double)ROUNDS);
}

TEST_F(StressTester, FILESIZE_1_MB) {
    char *s = NULL;
    mood_error_t  err = read_file("data/1mb.txt", &s);
    ASSERT_EQ(err, ERR_OK);

    double avg_cpu_time = 0;
    measure_average(s, &avg_cpu_time);

    StressTester::UpdateReport(1, avg_cpu_time);
    free(s);
}

TEST_F(StressTester, FILESIZE_10_MB) {
    char *s = NULL;
    mood_error_t  err = read_file("data/10mb.txt", &s);
    ASSERT_EQ(err, ERR_OK);

    double avg_cpu_time = 0;
    measure_average(s, &avg_cpu_time);

    StressTester::UpdateReport(10, avg_cpu_time);

    free(s);
}

TEST_F(StressTester, FILESIZE_100_MB) {
    char *s = NULL;
    mood_error_t  err = read_file("data/100mb.txt", &s);
    ASSERT_EQ(err, ERR_OK);

    double avg_cpu_time = 0;
    measure_average(s, &avg_cpu_time);

    StressTester::UpdateReport(100, avg_cpu_time);

    free(s);
}

TEST_F(StressTester, FILESIZE_1000_MB) {
    char *s = NULL;
    mood_error_t  err = read_file("data/1gb.txt", &s);
    ASSERT_EQ(err, ERR_OK);

    double avg_cpu_time = 0;
    measure_average(s, &avg_cpu_time);

    StressTester::UpdateReport(1000, avg_cpu_time);
    free(s);
}
