#include <stdio.h>
#include <mood/mood_determine.h>

int main( void ) {
    const char *const s = "Hello :) :( :( :((((:( a\n\0";

    mood_t mood;
    mood_error_t err = mood_determine(s, &mood);
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

    return 0;
}
