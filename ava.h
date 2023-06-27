#ifndef AVA_H
#define AVA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

char *createURL(const char*, const char*);
char *sendHttpsRequest(const char*);
unsigned int handleMemoryCallback(void*, size_t, size_t, void*);

struct HttpResponse {
	char *responseData;
	unsigned int responseSize;
};

struct SearchFlags {
	bool raw, quiet, all, debug, save_html, plus_urls;
};

#ifdef __cplusplus
};
#endif

#endif
