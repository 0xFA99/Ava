
#include "ava.h"
#include "cli.h"
#include "http.h"
#include "utils.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

static struct Ava *ava = NULL;

static int
ava_save_response(void)
{
    char *cache_dir = get_cache_dir();
    if (cache_dir == NULL)
        return -1;

    if (save_to_file(ava->response->data, cache_dir) == -1)
        return -1;
    
    free(cache_dir);
    
    return 0;
}

void
ava_init()
{
    ava = (struct Ava *)malloc(sizeof(struct Ava));
    if (ava == NULL) { 
        fprintf(stderr, "[ERROR] Failed to initialized Ava.\n");
        exit(EXIT_FAILURE);
    }

    ava->flag = (struct Flag *)malloc(sizeof(struct Flag));
    if (ava->flag == NULL) {
        fprintf(stderr, "[ERROR] Failed to initialized Ava Flags.\n");
        ava_cleanup();
        exit(EXIT_FAILURE);
    }
    
    ava->response = (struct Response *)malloc(sizeof(struct Response));
    if (ava->response == NULL) {
        fprintf(stderr, "[ERROR] Failed to initialized Ava Response.\n");
        ava_cleanup();
        exit(EXIT_FAILURE);
    }
}

void
ava_run(int argc, char *argv[])
{
    if (ava_get_flags(ava, argc, argv) == -1)
        return;

    send_http_request(ava);

    ava_parsing_init(ava);
    ava_parsing_run();
    ava_parsing_cleanup();


}

void
ava_cleanup()
{
    if (ava) {
        if (ava->response) {
            free(ava->response->data);
            free(ava->response);
        }
        
        free(ava->query);
        free(ava->flag);
        free(ava);
        
        ava = NULL;
    }
}

