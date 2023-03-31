#ifndef AVA_H
#define AVA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

char *set_url(const char*, const char*);
char *https_request(const char*);
static unsigned int memory_callback(void*, unsigned int, unsigned int, void*);

struct Response {
	char *data;
	unsigned int size;
};

bool raw = false;
bool quiet = false;
bool all = false;
bool best_match = false;
bool pick_search = false;
bool pick_lang = false;
bool debug = false;
bool save_html = false;
bool use_cache = false;
bool no_pipe = false;
bool plus_urls = false;

#ifdef __cplusplus
};
#endif

#endif
