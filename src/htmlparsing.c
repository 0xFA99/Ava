#include "htmlparsing.h"
#include "include/global.h"

#include <string.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpathInternals.h>

void
search_math(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)"//span[@jsname='VssY5c']", xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return;
    }

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    print_output(content);

    xmlFree(content);
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

void
search_lyric_us(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)"//span[@jsname='YS01Ge']", xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return;
    }

    for (int i = 0; i < nodes->nodeNr; i++) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar *context = xmlNodeGetContent(node);
        print_output(context);
        xmlFree(context);
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

void
search_currency(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)"//div[@id='_tnfeY6kZr42x4w_V0YrgDQ_184']/div/div/div[2]/div/div/div/div[4]/div/div/div/div", xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
    }

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    char *format = strtok(content, ",");
    print_output(format);

    xmlFree(content);
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

void
search_know_right(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)"//div[@class='kno-rdesc']/span", xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return;
    }

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    print_output(content);

    xmlFree(content);
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

void
search_unit(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)"", xpathCtx); // Soon
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return;
    }

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    print_output(content);

    xmlFree(content);
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

void
search_translate(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)"//pre[@id='tw-target-text']", xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return;
    }

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    print_output(content);

    xmlFree(content);
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

void
search_quotes(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)"//li[@class='TrT0Xe']", xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return;
    }

    for (int i = 0; i < nodes->nodeNr; i++) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar *content = xmlNodeGetContent(node);

        printf("%s\n", content);

        xmlFree(content);
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

void
search_lists(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)"//span[@class='hgKElc']", xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return;
    }

    for (int i = 0; i < nodes->nodeNr; i++) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar *content = xmlNodeGetContent(node);

        printf("%s\n", content);

        xmlFree(content);
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

void
search_weather(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *)"//div[@class='UQt4rd']", xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if ((nodes == NULL) || (nodes->nodeNr == 0)) {
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        return;
    }

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    /*
    char *output_buffer =  (char *) malloc(strlen((char *) content));
    char *output_ptr = output_buffer;
    size_t output_size = strlen((char *) content);

    iconv_t conv_desc = iconv_open("ISO-8859-1", "UTF-8");
    size_t result = iconv(conv_desc, &content, &output_size, &output_ptr, &output_size);

    if (result == (size_t) -1) {
        printf("Error: Conversion failed.\n");
        free(output_buffer);
        xmlFree(content);
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        exit(1);
    }

    iconv_close(conv_desc);

    printf("%s\n", output_buffer);

    free(output_buffer);
     */

    char *result = recode_string(content);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error: Conversion failed\n");
    }

    xmlFree(content);

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

void
parse_html(const char *response)
{
    htmlDocPtr doc;
    doc = htmlReadMemory(response, strlen(response), NULL, "ISO-8859-1",
                         HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);

    /* Test Every Function for XPath Expression ill add multithreading for
     * every function and for now ill make sure all function working well and
     * nothing memory issue
     */
    /*
    search_math(&doc);
    search_lyric_us(&doc);
    search_currency(&doc);
    search_know_right(&doc);
    search_unit(&doc);
    search_translate(&doc);
    search_quotes(&doc);
    search_lists(&doc);
     */
    search_weather(&doc);

    xmlFreeDoc(doc);
}