#include "ava.h"

#include "include/getting_html.h"
#include "include/global.h"
#include "include/save_to_file.h"
#include "include/htmlparsing.h"

#include "test/offline_doc.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cmake-build-debug/config.h"

void
print_help()
{
    printf("Usage: ava [options] query\n");
    printf("Options:\n");
    printf("-h Show this help message and exit.\n");
    printf("-v Print ava version info and exit.\n\n");
    printf("-r Raw search result.\n");
    printf("   (no pretty output, no colors)\n\n");
    printf("-q Only output search result.\n");
    printf("    (silences \"Did you mean?\", greeting, usage)\n\n");
    printf("-a Prints all valid answer.\n\n");
    printf("-u Prints out the top handful of URLs for your search query\n");
    printf("    (this is automatically printed out if ava can't find you an answer)\n\n");
    printf("-b Tries to select the best answer based on keywords at the start and end of your query.\n");
    printf("    (experimental - eg: define WORD, SONG lyrics, PERSON quotes, weather CITY, FILM cast)\n\n");
    printf("-t Pick answers to test.\n");
    printf("    (you can specify multiple answers using ava_NAME in your query)\n\n");
    printf("-l use LANG_[lang] in your query to override the language used\n");
    printf("    (eg: ava -l LANG_en_US my search query)\n\n");
    printf("ava supports the following environment variables:\n");
    printf("    AVA_LANG=[lang] sets default search language (eg: AVA_LANG='en_US')\n\n");
    printf("    AVA_DELAY=[int] if you find more than one answer is being printed (and you're not using -a)\n");
    printf("                    increase this number by a little (you want it to be as low as posibble)\n");
    printf("                    default value is 250 (eg: AVA_DELAY=270)\n\n");
    printf("developer flags:\n");
    printf("    -d prints debug info along with results\n");
    printf("    -s saves HTML for this query to $XDG_CACHE_HOME/ava/[date]-[query].html\n\n");
    printf("    -c use most recent cached result and query\n");
    printf("       this can be combined with -t flag to more quickly test for different answer\n\n");
    printf("    -p disable pipe support (it can break some scripts including our own test script)\n\n");
    printf("Report bugs at \n");
}

int
main(int argc, char *argv[])
{
    int c;
    char *query = NULL;

    while ((c = getopt(argc, argv, "rvhqabtldscpu:")) != -1) {
        switch (c) {
            case 'r':
                raw = true;
                break;
            case 'v':
                printf("ava Version %s\n", PROJECT_VER);
                break;
            case 'h':
                print_help();
                break;
            case 'q':
                quiet = true;
                break;
            case 'a':
                all = true;
                break;
            case 'b':
                best_match = true;
                break;
            case 't':
                pick_search = true;
                break;
            case 'l':
                pick_lang = true;
                break;
            case 'd':
                debug = true;
                break;
            case 's':
                save_html = true;
                break;
            case 'c':
                use_cache = true;
                break;
            case 'p':
                no_pipe = true;
                break;
            case 'u':
                plus_urls = true;
                break;
            case '?':
                fprintf(stderr, "Unrecognized option: '-%c'\n", optopt);
                break;
            default:
                break;
        }
    }

    if (argc > 1 && argv[argc - 1][0] != '-') {
        query = argv[argc - 1];
    }

    if (query == NULL) {
        printf("Usage: ava [options] query\n");
        return 1;
    }

    // HTML REQUEST
    char *response = https_request(query);

    if (save_html) {
        save_to_file(response);
    }

    // PROCESSING
    parse_html(response);

    free(response);

    return 0;
}
