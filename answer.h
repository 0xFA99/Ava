#ifndef ANSWER_H
#define ANSWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <libxml/xpathInternals.h>

#include "ava.h"

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"

xmlChar *getSingleAnswer(const char*);
xmlChar **getMultiAnswer(const char*);

void searchBasicInfo(const char*);
void searchCryptocurrencyInfo(const char*);
void searchCurrencyInfo(const char*);
void searchDateTimeInfo(const char*);
void searchDefinition(const char*);
void searchFeatures(const char*);
void searchKnowledgeRights(const char*);
void searchLists(const char*);
void searchHoliday(const char*);
void searchLyrics(const char*);
void searchMathematic(const char*);
void searchPronunciation(const char*);
void searchQuote(const char*);
void searchRichCast(const char*);
void searchTopLinks(const char*);
void searchTracklist(const char*);
void searchTranslation(const char*);
void searchUnitConversion(const char*);
void searchWeatherInfo(const char*);
// void search_know_top(const xmlXPathContextPtr*, const char*);

void parseHTML(struct SearchFlags, const char*);

#ifdef __cplusplus
};
#endif

#endif
