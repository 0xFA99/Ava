#ifndef AVA_H
#define AVA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

char *set_url(const char*, const char*);
char *https_request(const char*);
unsigned int memory_callback(void*, unsigned int, unsigned int, void*);

struct Response {
	char *data;
	unsigned int size;
};

struct Flags {
	bool raw, quiet, all, debug, save_html, plus_urls;
};

#ifdef __cplusplus
};
#endif

#endif
