#include "answer.h"

#include <libxml/HTMLparser.h>
#include <libxml/xmlstring.h>
#include <string.h>

#include "utils.h"
#include "config.h"

const char **answer_founds = NULL;

bool found_answer = false;
bool all_answer = false;
bool debug_flag = false;

short num_answers = 0;

void
add_answer(const char *new_answer)
{
	answer_founds = (const char **) realloc(answer_founds, (num_answers + 1) * sizeof(const char *));
	if (answer_founds == NULL) {
		printf("Failed to allocate memory\n");
	}

	answer_founds[num_answers] = new_answer;
	num_answers++;
}

bool
helper_single_answer(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return false;
	}

	if (!found_answer) found_answer = true;

	xmlNodePtr node = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);

	print_result((const char *) content);

	xmlFree(content);
	xmlXPathFreeObject(xpathObj);

	return true;
}

bool
helper_multi_answer(bool use_number, const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return false;
	}

	if (!found_answer) found_answer = true;

	puts(GREEN "-----" RESET);

	for (int i = 0; i < nodes->nodeNr; i++) {
		xmlNodePtr node = nodes->nodeTab[i];
		xmlChar *content = xmlNodeGetContent(node);

		if (use_number) {
			printf("%d. " YELLOW "%s\n" RESET, i + 1, content);
		} else {
			printf(YELLOW "%s\n" RESET, content);
		}

		xmlFree(content);
	}

	puts(GREEN "-----" RESET);

	xmlXPathFreeObject(xpathObj);

	return true;
}

void
search_math(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Math");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_lyrics(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_multi_answer(false, xpathCtx, xpath)) {
			add_answer("Lyric");
		}
	} else {
		helper_multi_answer(false, xpathCtx, xpath);
	}
}

void
search_translate(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Translate");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_currency(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Currency");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_quote(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Quote");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_holiday(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_multi_answer(true, xpathCtx, xpath)) {
			add_answer("Holiday");
		}
	} else {
		helper_multi_answer(true, xpathCtx, xpath);
	}
}

void
search_tracklist(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_multi_answer(true, xpathCtx, xpath)) {
			add_answer("Tracklist");
		}
	} else {
		helper_multi_answer(true, xpathCtx, xpath);
	}
}

void
search_know_right(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Know-Right");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_unit(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Unit");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
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

	if (!found_answer) found_answer = true;

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
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Datetime");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_pronounce(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Pronounce");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_basic(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Basic");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_feat(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Feat");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_lists(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_multi_answer(true, xpathCtx, xpath)) {
			add_answer("List");
		}
	} else {
		helper_multi_answer(true, xpathCtx, xpath);
	}
}

void
search_define(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_single_answer(xpathCtx, xpath)) {
			add_answer("Define");
		}
	} else {
		helper_single_answer(xpathCtx, xpath);
	}
}

void
search_richcast(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	if (debug_flag) {
		if (helper_multi_answer(true, xpathCtx, xpath)) {
			add_answer("Richcast");
		}
	} else {
		helper_multi_answer(true, xpathCtx, xpath);
	}
}

void
search_top_links(const xmlXPathContextPtr *xpathCtx, const char *xpath)
{
	xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) xpath, *xpathCtx);
	xmlNodeSetPtr nodes = xpathObj->nodesetval;

	if ((nodes == NULL) || (nodes->nodeNr == 0)) {
		xmlXPathFreeObject(xpathObj);
		return;
	}

	xmlXPathObjectPtr xpathObj2 = xmlXPathEvalExpression((xmlChar *) "//div[@class='yuRUbf']/a/@href", *xpathCtx);
	xmlNodeSetPtr nodes2 = xpathObj2->nodesetval;

	xmlNodePtr node = nodes->nodeTab[0];
	xmlNodePtr node2 = nodes->nodeTab[0];
	xmlChar *content = xmlNodeGetContent(node);
	xmlChar *content2 = xmlNodeGetContent(node2);

	puts("Sorry about that! Perhaps one of these links may be of use?\n");

	for (int i = 0; i < nodes->nodeNr; i++) {
		node = nodes->nodeTab[i];
		content = xmlNodeGetContent(node);

		node2 = nodes2->nodeTab[i];
		content2 = xmlNodeGetContent(node2);

		printf("%d. %s\n", i + 1, content);
		printf("%s\n\n", content2);
	}

	printf(GREEN "---\n" RESET);

	xmlFree(content);
	xmlFree(content2);
	xmlXPathFreeObject(xpathObj);
}

void
parse_html(bool flag_debug, bool flag_all, bool flag_quiet, const char *response)
{
	all_answer = flag_all;
	debug_flag = flag_debug;

	int response_len = (int) strlen(response);
	htmlDocPtr doc = htmlReadMemory(response, response_len, NULL, encode,
									HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR |
									HTML_PARSE_NOWARNING | HTML_PARSE_NONET);

	if (!doc)
		die("Failed to parse HTML content");

	xmlXPathContextPtr xpathCtx = xmlXPathNewContext(doc);

	if (!flag_quiet) {
		xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) "//a[@class='gL9Hy']/b", xpathCtx);
		xmlNodeSetPtr nodes = xpathObj->nodesetval;

		if ((nodes == NULL) || (nodes->nodeNr == 0)) {
			xmlXPathFreeObject(xpathObj);
		} else {
			xmlNodePtr node = nodes->nodeTab[0];
			xmlChar *content = xmlNodeGetContent(node);

			printf("> Did you mean: " BOLD "%s\n" RESET, content);

			xmlFree(content);
			xmlXPathFreeObject(xpathObj);
		}
	}

	void (*answers[])(const xmlXPathContextPtr*, const char*) = {
			search_tracklist, search_richcast, search_define, search_lists, search_pronounce,
			search_weather, search_math, search_unit, search_currency,
			search_holiday, search_basic, search_feat, search_quote,
			search_translate, search_lyrics, search_datetime,
			search_know_right
	};

	int size = sizeof(answer_list) / sizeof(answer_list[0]);

	if (all_answer) {
		for (int i = 0; i < size; i++) {
			(*answers[i])(&xpathCtx, answer_list[i]);
		}
	} else {
		int index = 0;
		while ((!found_answer) && (index < size)) {
			(*answers[index])(&xpathCtx, answer_list[index]);
			index++;
		}
	}

	if (!found_answer) {
		print_no_result();
		search_top_links(&xpathCtx, "//div[@class='yuRUbf']/a/h3");
	}

	if (debug_flag) {
		printf("Answer founds: ");
		if (num_answers == 0) {
			printf("No answer found!");
		} else {
			for (int i = 0; i < num_answers; i++) {
				printf("%s ", answer_founds[i]);
			}
		}
		printf("\n");
	}

	xmlXPathFreeContext(xpathCtx);
}
