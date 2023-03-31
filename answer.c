#include <libxml/HTMLparser.h>
#include <string.h>
#include <stdlib.h>

#include "answer.h"
#include "config.h"


void
search_math(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

        printf(GREEN "---\n" RESET);
        printf("%s\n", content);
        printf(GREEN "---\n" RESET);

	xmlFree(content);
	xmlXPathFreeObject(xpathObj);
}

void
search_lyric_us(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

        printf(GREEN "---\n" RESET);

	for (int i = 0; i < nodes->nodeNr; i++) {
		xmlNodePtr node = nodes->nodeTab[i];
		xmlChar *context = xmlNodeGetContent(node);

		printf(YELLOW "%s\n" RESET, context);

		xmlFree(context);
	}

        printf(GREEN "---\n" RESET);

	xmlXPathFreeObject(xpathObj);
}

void
search_translate(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        return;
    }

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    printf(GREEN "---\n" RESET);
    printf("%s\n", content);
    printf(GREEN "---\n" RESET);

    xmlFree(content);
    xmlXPathFreeObject(xpathObj);
}

void
search_currency(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        return;
    }

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    printf(GREEN "---\n" RESET);
    printf("%s\n", content);
    printf(GREEN "---\n" RESET);

    xmlFree(content);
    xmlXPathFreeObject(xpathObj);
}

void
search_quote(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        return;
    }

    printf(GREEN "---\n" RESET);

    for (int i = 0; i < nodes->nodeNr; i++) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar *context = xmlNodeGetContent(node);

	printf("%d. " YELLOW "%s\n" RESET, i + 1, context);

        xmlFree(context);
    }

    printf(GREEN "---\n" RESET);

    xmlXPathFreeObject(xpathObj);
}

void
search_holiday(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}
}

void
search_tracklist(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        return;
    }

    printf(GREEN "---\n" RESET);

    for (int i = 0; i < nodes->nodeNr; i++) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar *context = xmlNodeGetContent(node);

	printf("%d. " YELLOW "%s\n" RESET, i + 1, context);

        xmlFree(context);
    }

    printf(GREEN "---\n" RESET);

    xmlXPathFreeObject(xpathObj);
}

void
search_know_right(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        return;
    }

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    printf(GREEN "---\n" RESET);
    printf("%s\n", content);
    printf(GREEN "---\n" RESET);

    xmlFree(content);
    xmlXPathFreeObject(xpathObj);
}

void
search_unit(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

        printf(GREEN "---\n" RESET);
        printf("%s\n", content);
        printf(GREEN "---\n" RESET);

	xmlFree(content);
	xmlXPathFreeObject(xpathObj);
}

void
search_weather(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

        printf(GREEN "---\n" RESET);
	printf("%s°C\n", content);
        printf(GREEN "---\n" RESET);

	xmlFree(content);
	xmlXPathFreeObject(xpathObj);
}

void
search_datetime(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if ((nodes == NULL) || (nodes->nodeNr == 0)) {\
		xmlXPathFreeObject(xpathObj);
		return;
	}

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

        printf(GREEN "---\n" RESET);
	printf("%s\n", content);
        printf(GREEN "---\n" RESET);

	xmlFree(content);

	xmlXPathFreeObject(xpathObj);
}

void
search_pronounce(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if ((nodes == NULL) || (nodes->nodeNr == 0)) {\
		xmlXPathFreeObject(xpathObj);
		return;
	}

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

        printf(GREEN "---\n" RESET);
	printf("%s\n", content);
        printf(GREEN "---\n" RESET);

	xmlFree(content);

	xmlXPathFreeObject(xpathObj);
}

void
search_basic(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

        printf(GREEN "---\n" RESET);
	printf("%s\n", content);
        printf(GREEN "---\n" RESET);

	xmlFree(content);

	xmlXPathFreeObject(xpathObj);
}

void
search_feat(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

        printf(GREEN "---\n" RESET);
	printf("%s\n", content);
        printf(GREEN "---\n" RESET);

	xmlFree(content);

	xmlXPathFreeObject(xpathObj);
}

void
search_lists(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;
	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

        printf(GREEN "---\n" RESET);

	for (int i = 0; i < nodes->nodeNr; i++) {
		xmlNodePtr node = nodes->nodeTab[i];
		xmlChar *context = xmlNodeGetContent(node);

		printf("%d. " YELLOW "%s\n" RESET, i + 1, context);

		xmlFree(context);
	}

        printf(GREEN "---\n" RESET);

	xmlXPathFreeObject(xpathObj);
}

void
search_define(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

        printf(GREEN "---\n" RESET);
	printf("%s\n", content);
        printf(GREEN "---\n" RESET);

	xmlFree(content);

	xmlXPathFreeObject(xpathObj);
}

void
parse_html(bool quiet, const char *response)
{
	int response_len = (int) strlen(response);
	htmlDocPtr doc = htmlReadMemory(response, response_len, NULL, "UTF-8",
	                                HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR |
	                                HTML_PARSE_NOWARNING | HTML_PARSE_NONET);

	if (!doc) {
		fprintf(stderr, "Failed to parse HTML content");
		exit(1);
	}

	xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);

	if (!quiet) {
		xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) "//a[@class='gL9Hy']/b", xpathCtx);
		xmlNodeSetPtr nodes = xpathObj->nodesetval;

		if ((nodes == NULL) || (nodes->nodeNr == 0)) {
			xmlXPathFreeObject(xpathObj);
		} else {
			xmlNodePtr node = nodes->nodeTab[0];
			xmlChar *content = xmlNodeGetContent(node);

			printf("> Did you mean: ");
                        printf(BOLD "%s\n" RESET, content);

			xmlFree(content);

			xmlXPathFreeObject(xpathObj);
		}
	}

	search_tracklist(&xpathCtx, "//div[@class='title']");
	// richcast
	search_define(&xpathCtx, "//div[@jsname='x3Eknd']");
	search_lists(&xpathCtx, "//li[@class='TrT0Xe']");
	// kno-val
	search_pronounce(&xpathCtx, "//div[@class='TQ7enb']");
	// lyric_int
	search_weather(&xpathCtx, "//span[@id='wob_tm']");
	search_math(&xpathCtx, "//span[@jsname='VssY5c']");
	search_unit(&xpathCtx, "//div[@class='IZ6rdc']");
	search_currency(&xpathCtx, "//input[@jsname='NotFQb']");
	// know_top
	search_basic(&xpathCtx, "//div[@class='Z0LcW t2b5Cf']");
	search_feat(&xpathCtx, "//span[@class='hgKElc']");
	search_quote(&xpathCtx, "//div[@class='Qynugf']");
	search_translate(&xpathCtx, "//pre[@id='tw-target-text']");
	search_lyric_us(&xpathCtx, "//span[@jsname='YS01Ge']");
	search_datetime(&xpathCtx, "//div[@class='vk_bk dDoNo FzvWSb']");
	search_know_right(&xpathCtx, "//div[@jsname='g7W7Ed']/span");

	xmlXPathFreeContext(xpathCtx);
}
