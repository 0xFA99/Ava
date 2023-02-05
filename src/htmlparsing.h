#ifndef AVA_HTMLPARSING_H
#define AVA_HTMLPARSING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <libxml/HTMLparser.h>


void search_math(htmlDocPtr*);
void search_lyric_us(htmlDocPtr*);
void search_currency(htmlDocPtr*);
void search_know_right(htmlDocPtr*);
void search_unit(htmlDocPtr*);
void search_translate(htmlDocPtr*);
void search_quotes(htmlDocPtr*);
void search_lists(htmlDocPtr*);

void parse_html(const char*);

#ifdef __cplusplus
};
#endif

#endif //AVA_HTMLPARSING_H
