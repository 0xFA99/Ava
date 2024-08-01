
#ifndef AVA_UTILS_H
#define AVA_UTILS_H

#include "ava.h"

void read_string_file(struct Response *resp, const char *filename);
char *url_encode(const char *s);
char *get_cache_dir(void);
int save_to_file(const char *data, const char *directory);

#endif

