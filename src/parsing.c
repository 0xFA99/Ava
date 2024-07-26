
#include "ava.h"
#include "parsing.h"

#include <libxml/xmlstring.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpathInternals.h>

static struct Parsing parsingList[] = {
    { YOU_MEAN,         "//a[@class='gL9Hy']"                },
    { RICHCAST,         "//div[@class='JjtOHd']"             },
    { MATH,             "//span[@jsname='VssY5c']"           },
    { LYRIC,            "//span[@jsname='YS01Ge']"           },
    { TRANSLATE,        "//pre[@id='tw-target-text']"        },
    { CURRENCY,         "//input[@jsname='NotFQb']"          },
    { QUOTE,            "//div[@class='Qynugf']"             },
    { UNIT,             "//div[@class='IZ6rdc']"             },
    { HOLIDAY,          "//div[@class='c7r50']"              },
    { DEFINE,           "//div[@jsname='x3Eknd']"            },
    { TRACKLIST,        "//div[@class='title']"              },
    { KNOW_RIGHT,       "//div[@jsname='g7W7Ed']/span"       },
    { WEATHER,          "//span[@id='wob_tm']"               },
    { DATETIME,         "//div[@class='vk_bk dDoNo FzvWSb']" },
    { PRONOUNCE,        "//div[@class='TQ7enb']"             },
    { BASIC,            "//div[@class='Z0LcW t2b5Cf']"       },
    { FEAT,             "//span[@class='hgKElc']"            },
    { LISTS,            "//li[@class='TrT0Xe']"              },
};

static htmlDocPtr doc;
static xmlXPathContextPtr xpathCtx;

static xmlChar*
search_single_answer(const char *type, const char *xpath)
{
    xmlChar *result = NULL;

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)xpath, xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if (nodes != NULL) {
        xmlNodePtr node = nodes->nodeTab[0];
        result = xmlNodeGetContent(node);
    }

    xmlXPathFreeObject(xpathObj);
    
    return result;
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

    return 0;
}

int
ava_parsing_run()
{
    if (!ava->flag->quiet) {
        xmlChar *result = search_single_answer(parsingType[0].type, parsingType[0].xpath);
        printf("Did you mean: " BOLD "%s\n" RESET, result);
        xmlFree(result);
    }


}

void
ava_parsing_cleanup()
{
    xmlXPathFreeContext(xpathCtx);
}
