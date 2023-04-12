#ifndef ANSWER_H
#define ANSWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <libxml/xpathInternals.h>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"

bool helper_single_answer(const xmlXPathContextPtr*, const char*);
bool helper_multi_answer(bool, const xmlXPathContextPtr*, const char*);

void search_richcast(const xmlXPathContextPtr*, const char*);
void search_math(const xmlXPathContextPtr*, const char*);
void search_lyrics(const xmlXPathContextPtr*, const char*);
void search_translate(const xmlXPathContextPtr*, const char*);
void search_currency(const xmlXPathContextPtr*, const char*);
void search_quote(const xmlXPathContextPtr*, const char*);
void search_unit(const xmlXPathContextPtr*, const char*);
void search_holiday(const xmlXPathContextPtr*, const char*);
void search_define(const xmlXPathContextPtr*, const char*);
void search_tracklist(const xmlXPathContextPtr*, const char*);
void search_know_right(const xmlXPathContextPtr*, const char*);
void search_weather(const xmlXPathContextPtr*, const char*);
void search_datetime(const xmlXPathContextPtr*, const char*);
void search_pronounce(const xmlXPathContextPtr*, const char*);
void search_basic(const xmlXPathContextPtr*, const char*);
void search_feat(const xmlXPathContextPtr*, const char*);
void search_lists(const xmlXPathContextPtr*, const char*);
void search_top_links(const xmlXPathContextPtr*, const char*);

void parse_html(bool, bool, bool, const char*);
void add_answer(const char*);

#ifdef __cplusplus
};
#endif

#endif
