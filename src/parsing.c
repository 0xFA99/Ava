
#include <string.h>

#include "ava.h"
#include "utils.h"
#include "parsing.h"

#include <libxml/xmlstring.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpathInternals.h>

static struct Parsing parsingList[] = {
    { YOU_MEAN,         "//a[@class='gL9Hy']"               , NULL, search_single_answer },
    { RICHCAST,         "//div[@class='JjtOHd']"            , NULL, search_single_answer },
    { MATH,             "//span[@jsname='VssY5c']"          , NULL, search_single_answer },
    { LYRIC,            "//span[@jsname='YS01Ge']"          , NULL, search_single_answer },
    { TRANSLATE,        "//pre[@id='tw-target-text']"       , NULL, search_single_answer },
    { CURRENCY,         "//input[@jsname='NotFQb']"         , NULL, search_single_answer },
    { QUOTE,            "//div[@class='Qynugf']"            , NULL, search_single_answer },
    { UNIT,             "//div[@class='IZ6rdc']"            , NULL, search_single_answer },
    { HOLIDAY,          "//div[@class='c7r50']"             , NULL, search_single_answer },
    { DEFINE,           "//div[@jsname='x3Eknd']"           , NULL, search_single_answer },
    { TRACKLIST,        "//div[@class='title']"             , NULL, search_single_answer },
    { KNOW_RIGHT,       "//div[@jsname='g7W7Ed']/span"      , NULL, search_single_answer },
    { WEATHER,          "//span[@id='wob_tm']"              , NULL, search_single_answer },
    { DATETIME,         "//div[@class='vk_bk dDoNo FzvWSb']", NULL, search_single_answer },
    { PRONOUNCE,        "//div[@class='TQ7enb']"            , NULL, search_single_answer },
    { BASIC,            "//div[@class='Z0LcW t2b5Cf']"      , NULL, search_single_answer },
    { FEAT,             "//span[@class='hgKElc']"           , NULL, search_single_answer },
    { LISTS,            "//li[@class='TrT0Xe']"             , NULL, search_single_answer }
};

static htmlDocPtr doc;
static xmlXPathContextPtr xpathCtx;

void
search_single_answer(const char *xpath, char *data)
{
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)xpath, xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if (nodes && nodes->nodeNr > 0) {
        int size = 0;
        xmlChar *temp[nodes->nodeNr];

        for (int i = 0; i < nodes->nodeNr; i++) {
            temp[i] = xmlNodeGetContent(nodes->nodeTab[i]);
            size += xmlStrlen(temp[i]) + 1;
        }

        data = (char *)malloc(size);
        if (data == NULL) {
            fprintf(stderr, "[ERROR] Failed to allocate memory.\n");
            for (int i = 0; i < nodes->nodeNr; i++) {
                xmlFree(temp[i]);
            }

            xmlXPathFreeObject(xpathObj);
            exit(EXIT_FAILURE);
        }

        int current_pos = 0;
        for (int i = 0; i < nodes->nodeNr; i++) {
            int len = xmlStrlen(temp[i]);

            memcpy(data + current_pos, temp[i], len);
            current_pos += len;
            data[current_pos] = '\0';

            current_pos += 1;
            xmlFree(temp[i]);
        }

        data[current_pos] = '\0';
    }

    xmlXPathFreeObject(xpathObj);
}

int
ava_parsing_init(struct Ava *ava)
{
    doc = htmlReadMemory(ava->response->data, ava->response->size, NULL, "UTF-8",
                         HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR |
                         HTML_PARSE_NOWARNING | HTML_PARSE_NONET);

    if (!doc) {
        fprintf(stderr, "[ERROR] Failed to parsing HTML.\n");
        return -1;
    }

    xpathCtx = xmlXPathNewContext(doc);

    if (!ava->flag->quiet) {
        parsingList[0].process(parsingList[0].xpath, parsingList[0].data);
        if (parsingList[0].data != NULL) {
            printf(">> Did you mean: %s\n", parsingList[0].data);
        }
    }

    return 0;
}

int
ava_parsing_run(struct Ava *ava)
{
    // if (!ava->flag->quiet) {
    //     xmlChar *result = search_single_answer(parsingList[YOU_MEAN].type, parsingList[YOU_MEAN].xpath);
    //     if (result != NULL) {
    //         printf("Did you mean: " BOLD "%s\n" RESET, result);
    //         xmlFree(result);
    //     }
    // }

    return 0;
}

void
ava_parsing_cleanup()
{
    xmlXPathFreeContext(xpathCtx);

    for (int i = 0; i < PARSING_TYPE_CAP; i++) {
        if (parsingList[i].data != NULL) {
            free((void *)parsingList[i].data);

            parsingList[i].data = NULL;
        }
    }
}
