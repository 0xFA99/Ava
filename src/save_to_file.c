#include "include/save_to_file.h"
#include "include/global.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void
save_to_file(const char *response)
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%d-%T_ava", timeinfo);

    char filename[100];
    char *cache_dir = get_cache_dir();
    snprintf(filename, 100, "%s/%s.html", cache_dir, buffer);

    free(cache_dir);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    fprintf(file, "%s", response);
    printf("File saved in \'%s\'\n", filename);
    fclose(file);
}