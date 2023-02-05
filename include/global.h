#ifndef AVA_GLOBAL_H
#define AVA_GLOBAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// Global Options
extern bool raw;
extern bool quiet;
extern bool all;
extern bool best_match;
extern bool pick_search;
extern bool debug;
extern bool save_html;
extern bool use_cache;
extern bool pick_lang;
extern bool no_pipe;
extern bool plus_urls;

const char *get_os_lang();
char *get_cache_dir();
void print_output(unsigned char*);
void print_error();
char *recode_string(unsigned char*);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif //AVA_GLOBAL_H
