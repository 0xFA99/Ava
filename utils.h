#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

void die(const char *fmt, ...);
void save_to_file(const char *response);
char* get_cache_dir();
char *iso_8859_1_to_utf8(const char*);
void print_result(bool, const char*);
void print_no_result(bool);
void get_current_time(struct timespec*);

#ifdef __cplusplus
};
#endif

#endif
