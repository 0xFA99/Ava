#include "offline_doc.h"

#include <stdio.h>
#include <stdlib.h>

char*
get_doc(const char *path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *response = malloc(file_size + 1);
    if (response == NULL) {
        fclose(file);
        exit(1);
    }

    size_t bytes_read = fread(response, 1, file_size, file);
    if (bytes_read != file_size) {
        free(response);
        fclose(file);
        exit(1);
    }

    response[file_size] = '\0';

    return response;
}