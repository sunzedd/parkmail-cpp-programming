#include <reader_utils/read_file.h>

mood_error_t read_file(const char *const filepath, char *out_str) {
    if (out_str || !filepath) {
        return ERR_INVALID_ARG;
    }

    FILE *file = fopen(filepath, "r");
    if (!file) {
        return ERR_BAD_FILE;
    }

    mood_error_t err = ERR_OK;
    size_t file_size = 0;

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);

    if (file_size > 0) {
        out_str = (char *)malloc(sizeof(char) * file_size);
        if (out_str) {
            size_t bytes_read = fread(out_str, 1, file_size, file);
            if (bytes_read == 0) {
                err = ERR_BAD_FILE;
            }
        } else {
            err = ERR_BAD_ALLOC;
        }
    } else {
        err = ERR_EMPTY_FILE;
    }

    fclose(file);

    if (err != ERR_OK) {
        if (out_str) {
            free(out_str);
        }
    }

    return err;
}