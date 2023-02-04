#ifndef AVA_HTMLPARSING_H
#define AVA_HTMLPARSING_H

#include "include/global.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpathInternals.h>
#include <libxml/xpath.h>

bool
search_math(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    xpathCtx = xmlXPathNewContext(*doc);
    xpathObj = xmlXPathEvalExpression((xmlChar *) "//span[@jsname='VssY5c']", xpathCtx);

    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if (nodes->nodeNr == 0)
        return false;

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    print_output(content);

    xmlFree(content);

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);

    return true;
}

bool
search_lyric_us(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx = xmlXPathNewContext(*doc);
    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression((xmlChar *) "//span[@jsname='YS01Ge']", xpathCtx);
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    int size = (nodes) ? nodes->nodeNr : 0;
    if (nodes == NULL)
        return false;

    // Debug
    printf("Size: %d\n", size);

    for (int i = 0; i < size; i++) {
        xmlNodePtr node = nodes->nodeTab[i];
        xmlChar *content = xmlNodeGetContent(node);
        print_output(content);
        xmlFree(content);
    }

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

bool
search_currency(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    // create an XPath context
    xpathCtx = xmlXPathNewContext(*doc);

    // evaluate the XPath expression VssY5c
    xpathObj = xmlXPathEvalExpression((xmlChar *) "//div[@id='_tnfeY6kZr42x4w_V0YrgDQ_184']/div/div/div[2]/div/div/div/div[4]/div/div/div/div", xpathCtx);

    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    char *format = strtok(content, ",");
    print_output(format);

    xmlFree(content);

    // clean up
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
}

bool
search_know_right(htmlDocPtr *doc)
{
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    xpathCtx = xmlXPathNewContext(*doc);

    xpathObj = xmlXPathEvalExpression((xmlChar *)"//div[@class='kno-rdesc']/span", xpathCtx);

    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    if (nodes == NULL)
        return false;

    xmlNodePtr node = nodes->nodeTab[0];
    xmlChar *content = xmlNodeGetContent(node);

    print_output(content);

    xmlFree(content);

    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);

    return true;
}

void
parse_html(const char *response)
{
    htmlDocPtr doc;

    doc = htmlReadMemory(response, strlen(response), NULL, "ISO-8859-1",
                         HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);

    // search_lyric_us(&doc);
    // search_currency(&doc);
    /*
    if (!search_math(&doc))
        print_error();

    */
    if (!search_know_right(&doc))
        print_error();

    xmlFreeDoc(doc);
}

#endif //AVA_HTMLPARSING_H
