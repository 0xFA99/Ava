
#include <string.h>

#include "ava.h"
#include "utils.h"
#include "parsing.h"

#include <libxml/xmlstring.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpathInternals.h>

static struct Parsing parsingList[] = {
    { YOU_MEAN,         "//a[@class='gL9Hy']"               , NULL, get_xpath_content },
    { RICHCAST,         "//div[@class='JjtOHd']"            , NULL, get_xpath_content },
    { MATH,             "//span[@jsname='VssY5c']"          , NULL, get_xpath_content },
    { LYRIC,            "//span[@jsname='YS01Ge']"          , NULL, get_xpath_content },
    { TRANSLATE,        "//pre[@id='tw-target-text']"       , NULL, get_xpath_content },
    { CURRENCY,         "//span[@class='DFlfde SwHCTb']"    , NULL, get_xpath_content },
    { QUOTE,            "//div[@class='Qynugf']"            , NULL, get_xpath_content },
    { UNIT,             "//div[@class='IZ6rdc']"            , NULL, get_xpath_content },
    { HOLIDAY,          "//div[@class='c7r50']"             , NULL, get_xpath_content },
    { DEFINE,           "//div[@jsname='x3Eknd']"           , NULL, get_xpath_content },
    { TRACKLIST,        "//div[@class='title']"             , NULL, get_xpath_content },
    { KNOW_RIGHT,       "//div[@jsname='g7W7Ed']/span"      , NULL, get_xpath_content },
    { WEATHER,          "//span[@id='wob_tm']"              , NULL, get_xpath_content },
    { DATETIME,         "//div[@class='vk_bk dDoNo FzvWSb']", NULL, get_xpath_content },
    { PRONOUNCE,        "//div[@class='TQ7enb']"            , NULL, get_xpath_content },
    { BASIC,            "//div[@class='Z0LcW t2b5Cf']"      , NULL, get_xpath_content },
    { FEAT,             "//span[@class='hgKElc']"           , NULL, get_xpath_content },
    { LISTS,            "//li[@class='TrT0Xe']"             , NULL, get_xpath_content }
};

static htmlDocPtr doc;
static xmlXPathContextPtr xpathCtx;

void
get_xpath_content(const char *xpath, char **data)
{
    *data = NULL;

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)xpath, xpathCtx);
    if (xpathObj == NULL) {
        fprintf(stderr, "[ERROR] Failed to evaluate XPath expression.\n");
        return;
    }

    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    if (nodes == NULL || nodes->nodeNr == 0) {
        xmlXPathFreeObject(xpathObj);
        return;
    }

    int size = 0;
    xmlChar *temp[nodes->nodeNr];

    for (int i = 0; i < nodes->nodeNr; i++) {
        temp[i] = xmlNodeGetContent(nodes->nodeTab[i]);
        if (temp[i] != NULL) {
            size += xmlStrlen(temp[i]) + 1;
        }
    }

    *data = (char *)malloc(size + 1);
    if (*data == NULL) {
        fprintf(stderr, "[ERROR] Failed to allocate memory.\n");
        for (int i = 0; i < nodes->nodeNr; i++) {
            if (temp[i] != NULL) {
                xmlFree(temp[i]);
            }
        }

        xmlXPathFreeObject(xpathObj);
        exit(EXIT_FAILURE);
    }

    int current_pos = 0;
    for (int i = 0; i < nodes->nodeNr; i++) {
        if (temp[i] != NULL) {
            int len = xmlStrlen(temp[i]);

            memcpy(*data + current_pos, temp[i], len);
            current_pos += len;
            (*data)[current_pos] = '\0';

            current_pos += 1;
            xmlFree(temp[i]);
        }
    }

    (*data)[current_pos] = '\0';

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
    if (xpathCtx == NULL) {
        fprintf(stderr, "[ERROR] Failed to create XPath context!\n");
        xmlFreeDoc(doc);
        return -1;
    }

    return 0;
}

int
ava_parsing_run(struct Ava *ava)
{
    if (ava->flag->quiet == false) {
        parsingList[0].process(parsingList[0].xpath, &parsingList[0].data);
        if (parsingList[0].data != NULL) {
            printf(">> Did you mean: %s\n", parsingList[0].data);
        }
    }

	for (int i = 1; i < PARSING_TYPE_CAP; i++) {
		parsingList[i].process(parsingList[i].xpath, &parsingList[i].data);
	}

	for (int i = 1; i < PARSING_TYPE_CAP; i++) {
		if (parsingList[i].data != NULL) {
			printf("\n%s\n", result + 1, parsingList[i].data);
		}
	}

    printf("\n");

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

    xmlFreeDoc(doc);
}
