
#ifndef AVA_H
#define AVA_H

#include <stdlib.h>
#include <stdbool.h>

#define AVA_VERSION "0.1.0"

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define RED         "\033[1;31m"
#define GREEN       "\033[1;32m"
#define YELLOW      "\033[1;33m"
#define MAGENTA     "\033[1;35m"
#define CYAN        "\033[1;36m"

struct Flag {
    bool raw, quiet, all, debug, save, url;
};

struct Response {
    char *data;
    size_t size;
};

struct Ava {
    char *query;
    struct Flag *flag;
    struct Response *response;
};

void ava_init(void);
void ava_run(int argc, char *argv[]);
void ava_cleanup(void);

#endif

