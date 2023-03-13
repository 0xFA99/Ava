#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <iconv.h>

#include "utils.h"

void
die(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
        fputc(' ', stderr);
        perror(NULL);
    } else {
        fputc('\n', stderr);
    }

    exit(1);
}

char*
get_cache_dir()
{
    char *cache_dir = getenv("XDG_CACHE_HOME");
    if (!cache_dir || !cache_dir[0]) {
        char *home_dir = getenv("HOME");
        if (!home_dir || !home_dir[0])
            die("Cant access home directory!\n");

        unsigned int len = strlen(home_dir) + strlen("/.cache/") + strlen("ava") + 1;
        cache_dir = malloc(len);
        snprintf((char *) cache_dir, len, "%s/.cache/%s", home_dir, "ava");
    }

    int ret = mkdir(cache_dir, 0755);
    if (ret != 0 && errno != EEXIST)
        perror("mkdir");

    return cache_dir;
}

char*
recode_string(unsigned char *text)
{
    size_t len = strlen((char *) text);
    char *output_buffer = (char *) calloc(len + 1, sizeof(char));
    char *output_ptr = output_buffer;
    size_t output_size = len;

    iconv_t conv_desc = iconv_open("ISO-8859-1", "UTF-8");
    if (conv_desc == (iconv_t) -1) {
        free(output_buffer);
        return NULL;
    }

    size_t result = iconv(conv_desc, &text, &output_size, &output_ptr, &output_size);

    if (result == (size_t) - 1) {
        free(output_buffer);
        return (char *) text;
    }

    iconv_close(conv_desc);
    return output_buffer;
}

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
