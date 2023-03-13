#include <string.h>
#include <libxml/xpathInternals.h>
#include <libxml/HTMLparser.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "config.h"
#include "utils.h"

char *set_url(const char*, const char*);
char *https_request(const char *);
void search_math(htmlDocPtr*);
void search_lyric_us(htmlDocPtr*);
void search_currency(htmlDocPtr*);
void search_know_right(htmlDocPtr*);
void search_unit(htmlDocPtr*);
void search_translate(htmlDocPtr*);
void search_quotes(htmlDocPtr*);
void search_lists(htmlDocPtr*);
void search_weather(htmlDocPtr*);
void parse_html(const char*);
void print_output(unsigned char*);
void print_error();
static unsigned int memory_callback(void*, unsigned int, unsigned int, void *);

struct Response {
    char *data;
    unsigned int size;
};
// =======================

unsigned int
memory_callback(void *content, unsigned int size, unsigned int nmemb, void *userp)
{
    struct Response *response = (struct Response *) userp;
    unsigned int realsize = size * nmemb;
    response->data = realloc(response->data, response->size + realsize + 1);
    if (response->data == NULL) {
        fprintf(stderr, "Out of memory!\n");
        return 1;
    }

    memcpy(&(response->data[response->size]), content, realsize);
    response->size += realsize;
    response->data[response->size] = 0;

    return realsize;
}

char*
set_url(const char *lang, const char *text)
{
    char *result = NULL;

    unsigned int lang_len = strlen("hl=") + strlen(lang) + 1;
    unsigned int text_len = strlen("q=") + strlen(text) + 1;
    char *language = malloc(lang_len);
    char *query = malloc(text_len);

    snprintf(language, lang_len, "%s%s", "hl=", lang);
    snprintf(query, text_len, "%s%s", "q=", text);

    CURLU *newURL = curl_url();
    curl_url_set(newURL, CURLUPART_SCHEME, "https", 0);
    curl_url_set(newURL, CURLUPART_URL, search_engine_url, 0);
    curl_url_set(newURL, CURLUPART_PATH, "search", 0);
    curl_url_set(newURL, CURLUPART_QUERY, language, CURLU_APPENDQUERY);
    curl_url_set(newURL, CURLUPART_QUERY, query, CURLU_APPENDQUERY | CURLU_URLENCODE);
    curl_url_set(newURL, CURLUPART_URL, &result, 0);

    char *dump_result = strdup(result);

    free(result);
    free(language);
    free(query);

    curl_url_cleanup(newURL);

    return dump_result;
}

char*
https_request(const char *query)
{
    char *url = set_url(getenv("LANG"), query);
    char *dump_response = NULL;

    CURL *curl;
    CURLcode res;
    struct Response response;

    response.data = malloc(1);
    response.size = 0;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memory_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        if ((res = curl_easy_perform(curl)) != CURLE_OK)
            fprintf(stderr, "curl_easy_perform, failed: %s\n", curl_easy_strerror(res));

        dump_response = strdup(response.data);

        curl_easy_cleanup(curl);
        free(response.data);
        free(url);
    }

    return dump_response;
}

void
parse_html(const char *response)
{
    htmlDocPtr doc = htmlReadMemory(response, strlen(response), NULL, "ISO-8859-1",
            HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);

    xmlFreeDoc(doc);
}

void
print_output(unsigned char *output)
{
    printf("---\n");
    printf("%s\n", output);
    printf("---\n");
}

void
print_error()
{
    printf("---\n");
    printf("No Result !\n");
    printf("---\n");
}

// =======================

int
main(int argc, char *argv[])
{

    return 0;
}
