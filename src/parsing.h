
#ifndef AVA_PARSING_H
#define AVA_PARSING_H

#define PARSING_TYPE_CAP 18

#include "ava.h"

enum ParsingType {
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
    BASIC,
    FEAT,
    LISTS
};

struct Parsing {
    enum ParsingType type;
    char *xpath;
    char *data;
    void (*process)(const char *xpath, char *data);
};

int ava_parsing_init(struct Ava *ava);
int ava_parsing_run(struct Ava *ava);
void ava_parsing_cleanup(void);

void search_single_answer(const char *xpath, char *data);

#endif
