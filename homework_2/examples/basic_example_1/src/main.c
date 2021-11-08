#include <mood/mood_determine.h>
#include <reader_utils/read_file.h>
#include <stdio.h>
#include <stdlib.h>

void print_usage() {
    printf("\n");
    printf("homework_2 usage:\n");
    printf("\thomework_2 <filepath>\n\n");
}

void print_error(mood_error_t error) {
    switch (error) {
        case ERR_OK:
            printf("no errors occurred\n");
            break;
        case ERR_INVALID_ARG:
            printf("error: invalid argument\n");
            break;
        case ERR_NULLPTR_REFERENCE:
            printf("error: usage of NULL-pointer\n");
            break;
        case ERR_BAD_ALLOC:
            printf("error: failed to allocate heap memory\n");
            break;
        case ERR_BAD_FILE:
            printf("error: file does not exists\n");
            break;
        case ERR_EMPTY_FILE:
            printf("error: file is empty\n");
            break;
        case ERR_SHARED_MEM_BAD_RELEASE:
            printf("error: failed to release shared memory block\n");
            break;
        case ERR_SHARED_MEM_BAD_ALLOC:
            printf("error: failed to allocate shared memory block\n");
            break;
        case ERR_PROC_CREATE_FAILURE:
            printf("error: failed to fork child process\n");
            break;
        default:
            printf("error: unknown\n");
            break;
    }
}

void print_mood(mood_t mood) {
    printf("Mood is ");
    switch (mood) {
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
        mood_t mood = MOOD_NEUTRAL;
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
