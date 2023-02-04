#ifndef AVA_GETTING_HTML_H
#define AVA_GETTING_HTML_H

#ifdef __cplusplus
extern "C" {
#endif

struct Response {
    char *data;
    unsigned int size;
};

char *set_url(const char*, const char*);
static unsigned int memory_callback(void*, unsigned int, unsigned int, void*);
char *https_request(const char*);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif //AVA_GETTING_HTML_H
