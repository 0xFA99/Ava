
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>

#include "utils.h"

char*
read_string_file(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "[ERROR] Failed to open file: %s.\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "[ERROR] Failed to allocating memori to read file.\n");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        fprintf(stderr, "[ERROR] Failed reading file.\n");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(file);

    return buffer;
}

char*
url_encode(const char *s)
{
    if (s == NULL) return NULL;

    int len = strlen(s);
    char *encoded = malloc(len*3 + 1);

    if (encoded == NULL) return NULL;

    char *p = encoded;
    for (int i = 0; i < len; ++i) {
        if (isalnum(s[i]) || s[i] == '-' || s[i] == '_' || s[i] == '.' || s[i] == '~') {
            *p++ = s[i];
        } else {
            *p++ = '%';
            sprintf(p, "%02X", (unsigned char)s[i]);
            p += 2;
        }
    }

    *p = '\0';
    return encoded;
}

char*
get_cache_dir(void)
{
    char *cache_dir = getenv("XDG_CACHE_HOME");
    if (!cache_dir || !cache_dir[0]) {
        char *home_dir = getenv("HOME");
        if (!home_dir || !home_dir[0]) {
            fprintf(stderr, "[ERROR] Cant Access home directory!\n");
            return NULL;
        }

        unsigned int len = strlen(home_dir) + strlen("./cache/") + strlen("ava") + 1;
        cache_dir = (char *)malloc(len);

        snprintf((char *)cache_dir, len, "%s/.cache/%s", home_dir, "ava");
    }

    int ret = mkdir(cache_dir, 0755);
    if (ret != 0 && errno != EEXIST) {
        fprintf(stderr, "[ERROR] Failed to make Ava cacher directory.\n");
        return NULL;
    }

    return cache_dir;
}

int
save_to_file(const char *data, const char *directory)
{
    time_t rawtime;
    struct tm *timeinfo;
    char  buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%d-%T_ava", timeinfo);

    char filename[100];
    snprintf(filename, 100, "%s/%s.html", directory, buffer);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "[ERROR] Failed to write file.\n");
        return -1;
    }

    fprintf(file, "%s", data);
    fprintf(stdout, "[INFO] File saved in \'%s\'\n", filename);

    fclose(file);

    return 0;
}
