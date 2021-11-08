#include <mood/mood_determine.h>
#include <reader_utils/read_file.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR_STRING_SIZE 64

void print_usage() {
    printf("\n");
    printf("homework_2 usage:\n");
    printf("\thomework_2 <filepath>\n\n");
}
void print_error(mood_error_t error) {
    char error_string[ERROR_STRING_SIZE];
    get_error_string(error, error_string);
    printf("Error has occurred: %s\n", error_string);
}
void print_mood(mood_t mood) {
    printf("Mood is ");
    switch (mood)
    {
    case MOOD_NEUTRAL:
        printf("neutral\n");
        break;
    case MOOD_NEGATIVE:
        printf("negative\n");
        break;
    case MOOD_POSITIVE:
        printf("positive\n");
        break;
    default:
        printf("unknown\n");
        break;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        print_usage();
        return 0;
    }

    char *data = NULL;
    mood_error_t err = read_file(argv[1], &data);
    
    if (!err) {
        mood_t mood;
        err = mood_determine(data, &mood);
        if (!err) {
            print_mood(mood);
        }
    }

    if (err) {
        print_error(err);
    }
    if (data) {
        free(data);
    }

    return 0;
}
