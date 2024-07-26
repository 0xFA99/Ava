
#include "ava.h"
#include "parsing.h"

#include <libxml/xmlstring.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpathInternals.h>

static struct ParsingType parsingType[] = {
    { "Richcast",       "//div[@class='JjtOHd']"             },
    { "Math",           "//span[@jsname='VssY5c']"           },
    { "Lyric",          "//span[@jsname='YS01Ge']"           },
    { "Translate",      "//pre[@id='tw-target-text']"        },
    { "Currency",       "//input[@jsname='NotFQb']"          },
    { "Quote",          "//div[@class='Qynugf']"             },
    { "Unit",           "//div[@class='IZ6rdc']"             },
    { "Holiday",        "//div[@class='c7r50']"              },
    { "Define",         "//div[@jsname='x3Eknd']"            },
    { "Tracklist",      "//div[@class='title']"              },
    { "Know Right",     "//div[@jsname='g7W7Ed']/span"       },
    { "Weather",        "//span[@id='wob_tm']"               },
    { "Datetime",       "//div[@class='vk_bk dDoNo FzvWSb']" },
    { "Pronounce",      "//div[@class='TQ7enb']"             },
    { "Basic",          "//div[@class='Z0LcW t2b5Cf']"       },
    { "Feat",           "//span[@class='hgKElc']"            },
    { "Lists",          "//li[@class='TrT0Xe']"              },
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

    return 0;
}

int
ava_parsing_run()
{
    // TODO: Something
}

void
ava_parsing_cleanup()
{
    xmlXPathFreeContext(xpathCtx);
}
