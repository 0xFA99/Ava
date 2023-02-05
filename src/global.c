#include "include/global.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <iconv.h>

bool raw = false;
bool quiet = false;
bool all = false;
bool best_match = false;
bool pick_search = false;
bool debug = false;
bool save_html = false;
bool use_cache = false;
bool pick_lang = false;
bool no_pipe = false;
bool plus_urls = false;

const char*
get_os_lang()
{
    const char *lang = getenv("LANG");

    return lang;
}

char*
get_cache_dir()
{
    char *cache_dir = getenv("XDG_CACHE_HOME");
    if (!cache_dir || !cache_dir[0]) {
        char *home_dir = getenv("HOME");
        if (!home_dir || !home_dir[0]) {
            fprintf(stderr, "Cant access home directory!\n");
        }

        unsigned int len = strlen(home_dir) + strlen("/.cache/") + strlen("ava") + 1;
        cache_dir = malloc(len);
        snprintf((char *)cache_dir, len, "%s/.cache/%s", home_dir, "ava");
    }

    int ret = mkdir(cache_dir, 0755);
    if (ret != 0 && errno != EEXIST) {
        perror("mkdir");
    }

    return cache_dir;
}

void
print_output(unsigned char *output)
{
    printf("---\n");
    printf("%s\n", output);
    printf("---\n");

    EXIT_SUCCESS;
}

void
print_error()
{
    printf("---\n");
    printf("No Result !\n");
    printf("---\n");
}

char*
recode_string(unsigned char *text)
{
    size_t len = strlen((char *)text);
    char *output_buffer = (char *) calloc(len + 1, sizeof(char));
    char *output_ptr = output_buffer;
    size_t output_size = len;

    iconv_t conv_desc = iconv_open("ISO-8859-1", "UTF-8");
    if(conv_desc == (iconv_t) -1) {
        free(output_buffer);
        return NULL;
    }

    size_t result = iconv(conv_desc, &text, &output_size, &output_ptr, &output_size);

    if (result == (size_t) -1) {
        free(output_buffer);
        return (char *)text;
    }

    iconv_close(conv_desc);
    return output_buffer;
}