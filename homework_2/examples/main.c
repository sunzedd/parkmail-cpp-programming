#include <mood/mood_determine.h>
#include <reader_utils/read_file.h>
#include <stdio.h>

int main( void ) {
    char *s = NULL;
    mood_error_t err = ERR_OK;
    err = read_file("/home/sunz/park_mail/parkmail-cpp-programming/homework_2/examples/data/1.txt", &s);
    if (err != ERR_OK) {
        printf("error has occurred: %d", err);
        return 0;
    }

    mood_t mood = 0;
    err = mood_determine(s, &mood);
    if (err == ERR_OK) {
        printf("mood is ");
        switch (mood) {
            case NEUTRAL:  printf("neutral\n"); break;
            case NEGATIVE: printf("negative\n"); break;
            case POSITIVE: printf("positive\n"); break;
            default:       printf("unexpected result\n"); break;
        }
    } else {
        printf("error occurred\n");
    }

    free(s);
    return 0;
}
