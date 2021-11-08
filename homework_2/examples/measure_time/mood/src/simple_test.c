#include <reader_utils/read_file.h>
#include <mood/mood_determine.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *s = NULL;
    mood_error_t err = read_file("data/1gb.txt", &s);
    if (err) {
        printf("error while reading file\n");
        return err;
    }

    mood_t mood = MOOD_NEUTRAL;
    err = mood_determine(s, &mood);
    printf("mood code is %d", mood);

    free(s);
    return 0;
}
