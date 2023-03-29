#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <iconv.h>

#include <sys/stat.h>

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
get_cache_dir(void)
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
iso8859_1_to_utf8(const char *iso8859_1_str)
{
    size_t iso8859_1_len = strlen(iso8859_1_str);
    size_t utf8_len = iso8859_1_len * 4;
    char *utf8_str = (char *)malloc(utf8_len);

    iconv_t conv = iconv_open("UTF-8", "ISO-8859-1");
    
    if (conv == (iconv_t)(1)) {
        exit(1);
    }

    char *in_buf = (char *)iso8859_1_str;
    char *out_buf = utf8_str;
    size_t in_len = iso8859_1_len;
    size_t out_len = utf8_len;

    if (iconv(conv, &in_buf, &in_len, &out_buf, &out_len) == (size_t)(-1)) {
        exit(1);
    }

    iconv_close(conv);
    utf8_str[utf8_len - out_len] = '\0';

    return utf8_str;
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

void
print_result(const char *result)
{
    printf("---\n%s\n---\n", result);
}

void
print_no_result(void)
{
    printf("---\nNo result!\n---\n");
}
