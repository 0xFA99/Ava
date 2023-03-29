#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

void die(const char *fmt, ...);
void save_to_file(const char *response);
char* get_cache_dir();
char *iso_8859_1_to_utf8(const char*);
void print_result(const char*);
void print_no_result();

#ifdef __cplusplus
};
#endif

#endif
