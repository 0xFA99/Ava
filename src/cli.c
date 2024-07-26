
#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static struct option long_opts[] = {
    { "raw",        no_argument, NULL, 'r' },
    { "version",    no_argument, NULL, 'v' },
    { "help",       no_argument, NULL, 'h' },
    { "quiet",      no_argument, NULL, 'q' },
    { "all",        no_argument, NULL, 'a' },
    { "debug",      no_argument, NULL, 'd' },
    { "save",       no_argument, NULL, 's' },
    { "url",        no_argument, NULL, 'u' }
};

int
ava_get_flags(struct Ava *ava, int argc, char *argv[])
{
    int opt;
    while ((opt = getopt_long(argc, argv, "rvhqadsu", long_opts, NULL)) != -1) {
        switch (opt) {
            case 'r':
                ava->flag->raw = true; break;
            case 'v':
                printf("Ava Version: %s\n", AVA_VERSION); return -1;
            case 'h':
                printf(GREEN "Usage: " RESET "ava " YELLOW "[options] " MAGENTA "\"query\"\n"); return -1;
            case 'q':
                ava->flag->quiet = true; break;
            case 'a':
                ava->flag->all = true; break;
            case 'd':
                ava->flag->debug = true; break;
            case 's':
                ava->flag->save = true; break;
            case 'u':
                ava->flag->url = true; break;
            case '?':
                fprintf(stderr, "[ERROR] Invalid option.\n"); break;
            default:
                fprintf(stderr, "[ERROR] Unknown option.\n"); break;
        }
    }

    if (argc > optind) {

        int query_len = strlen(argv[argc - 1]) + 1;

        ava->query = (char *)malloc(query_len);
        if (ava->query == NULL) {
            fprintf(stderr, "[ERROR] Failed to get query.\n");
            return -1;
        }

        strncpy(ava->query, argv[argc - 1], query_len);
        ava->query[query_len] = '\0';

    } else {
        fprintf(stderr, "[ERROR] No query.\n");
    }

    return 0;
}

