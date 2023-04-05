#include <libxml/HTMLparser.h>
#include <libxml/xmlstring.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "answer.h"
#include "config.h"

bool found_answer = false;

void
helper_single_answer(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        return;
    }

	if (found_answer == false)
		found_answer = true;

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

	print_result((const char *) content);

    xmlFree(content);
    xmlXPathFreeObject(xpathObj);
}

void
helper_multi_answer(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

	if (found_answer != true)
		found_answer = true;

	puts(GREEN "---" RESET);

	for (int i = 0; i < nodes->nodeNr; i++) {
		xmlNodePtr node = nodes->nodeTab[i];
		xmlChar *context = xmlNodeGetContent(node);

		printf("%d. " YELLOW "%s\n" RESET, i + 1, context);

		xmlFree(context);
	}

	puts(GREEN "---" RESET);

	xmlXPathFreeObject(xpathObj);
}

void
search_math(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_single_answer(xpathCtx, xpath);
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

	if (found_answer != true)
		found_answer = true;

	puts(GREEN "---" RESET);

	for (int i = 0; i < nodes->nodeNr; i++) {
		xmlNodePtr node = nodes->nodeTab[i];
		xmlChar *context = xmlNodeGetContent(node);

		printf(YELLOW "%s\n" RESET, context);

		xmlFree(context);
	}

	puts(GREEN "---" RESET);

	xmlXPathFreeObject(xpathObj);
}

void
search_translate(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_single_answer(xpathCtx, xpath);
}

void
search_currency(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_single_answer(xpathCtx, xpath);
}

void
search_quote(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_multi_answer(xpathCtx, xpath);
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

	if (found_answer != true)
		found_answer = true;

	for (int i = 0; i < nodes->nodeNr; i++) {
		xmlNodePtr node = nodes->nodeTab[i];
		xmlChar *content = xmlNodeGetContent(node);

		printf("%s\n", content);

		xmlFree(content);
	}

	xmlXPathFreeObject(xpathObj);
}

void
search_tracklist(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_multi_answer(xpathCtx, xpath);
}

void
search_know_right(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_single_answer(xpathCtx, xpath);
}

void
search_unit(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_single_answer(xpathCtx, xpath);
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

	if (found_answer != true)
		found_answer = true;

	printf(GREEN "---\n" RESET);

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

	printf("Temperature: %s°C\n", content);

	xpathObj = xmlXPathEvalExpression((xmlChar *) "//div[@class='wtsRwe']/div", *xpathCtx);
	nodes = xpathObj->nodesetval;

	for (int i = 0; i < nodes->nodeNr; i++) {
		node = nodes->nodeTab[i];
		content = xmlNodeGetContent(node);
		printf("%s\n", content);
	}

	printf(GREEN "---\n" RESET);

	xmlFree(content);
	xmlXPathFreeObject(xpathObj);
}

void
search_datetime(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_single_answer(xpathCtx, xpath);
}

void
search_pronounce(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_single_answer(xpathCtx, xpath);
}

void
search_basic(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_single_answer(xpathCtx, xpath);
}

void
search_feat(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_single_answer(xpathCtx, xpath);
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

	if (found_answer != true)
		found_answer = true;

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
	helper_single_answer(xpathCtx, xpath);
}

void
search_richcast(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	helper_multi_answer(xpathCtx, xpath);
}

void
parse_html(bool quiet, const char *response)
{
	int response_len = (int) strlen(response);
	htmlDocPtr doc = htmlReadMemory(response, response_len, NULL, encode,
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

	void (*answers[])(const xmlXPathContextPtr*, const char*) = {
			search_tracklist, search_richcast, search_define, search_lists, search_pronounce,
			search_weather, search_math, search_unit, search_currency,
			search_holiday, search_basic, search_feat, search_quote,
			search_translate, search_lyric_us, search_datetime,
			search_know_right
	};

	int index = 0;
	int size = sizeof(answer_list) / sizeof(answer_list[0]);
	while (found_answer != true && index < size) {
		(*answers[index])(&xpathCtx, answer_list[index]);

		index++;
	}

	// search_tracklist(&xpathCtx, "//div[@class='title']"),
	// search_define(&xpathCtx, "//div[@jsname='x3Eknd']"),
	// search_lists(&xpathCtx, "//li[@class='TrT0Xe']"),
	// search_pronounce(&xpathCtx, "//div[@class='TQ7enb']"),
	// search_weather(&xpathCtx, "//span[@id='wob_tm']"),
	// search_math(&xpathCtx, "//span[@jsname='VssY5c']"),
	// search_unit(&xpathCtx, "//div[@class='IZ6rdc']"),
	// search_currency(&xpathCtx, "//input[@jsname='NotFQb']"),
	// search_holiday(&xpathCtx, "//div[@class='c7r50']"),
	// search_basic(&xpathCtx, "//div[@class='Z0LcW t2b5Cf']"),
	// search_feat(&xpathCtx, "//span[@class='hgKElc']"),
	// search_quote(&xpathCtx, "//div[@class='Qynugf']"),
	// search_translate(&xpathCtx, "//pre[@id='tw-target-text']"),
	// search_lyric_us(&xpathCtx, "//span[@jsname='YS01Ge']"),
	// search_datetime(&xpathCtx, "//div[@class='vk_bk dDoNo FzvWSb']"),
	// search_know_right(&xpathCtx, "//div[@jsname='g7W7Ed']/span")


	xmlXPathFreeContext(xpathCtx);

	if (found_answer == false)
		print_no_result();
}
