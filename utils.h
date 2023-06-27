#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <libxml/HTMLparser.h>

char *getCacheDirectory(void);
char *convertLatin1ToUtf8(const char*);

void exitWithError(const char *fmt, ...);
void saveResponseToFile(const char*);
void getCurrentTime(struct timespec*);

void printSingleResult(bool, const char*);
void printResultList(bool, bool, int, xmlChar**);
void printMultiList(bool, bool, bool, int, xmlChar**, xmlChar**);
void printNoResult(bool);

void freeXmlCharList(xmlChar**);
void freeXmlChar(xmlChar*);

#ifdef __cplusplus
};
#endif

#endif
