
#ifndef AVA_PARSING_H
#define AVA_PARSING_H

#include "ava.h"

enum parsingType {
    YOU_MEAN = 0,
    RICHCAST,
    MATH,
    LYRIC,
    TRANSLATE,
    CURRENCY,
    QUOTE,
    UNIT,
    HOLIDAY,
    DEFINE,
    TRACKLIST,
    KNOW_RIGHT,
    WEATHER,
    DATETIME,
    PRONOUNCE,
    BASIC
    FEAT,
    LISTS
};

struct Parsing {
    enum parsingType type;
    char *xpath;
};

int ava_parsing_init(struct Ava *ava);
int ava_parsing_run(void);
void ava_parsing_cleanup(void);

#endif
