
#ifndef AVA_PARSING_H
#define AVA_PARSING_H

#include "ava.h"

struct ParsingType {
    char type[20];
    char xpath[50];
};

int ava_parsing_init(struct Ava *ava);
int ava_parsing_run(void);
void ava_parsing_cleanup(void);

#endif
