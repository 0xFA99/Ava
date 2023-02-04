#include "getting_html.h"
#include "include/global.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

const char *user_agent = "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) QtWebEngine/5.15.2 Chrome/87.0.4280.144 Safari/537.36";

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
    curl_url_set(newURL, CURLUPART_URL, "https://www.google.com/", 0);
    curl_url_set(newURL, CURLUPART_PATH, "search", 0);
    curl_url_set(newURL, CURLUPART_QUERY, language, CURLU_APPENDQUERY);
    curl_url_set(newURL, CURLUPART_QUERY, query, CURLU_APPENDQUERY | CURLU_URLENCODE);

    curl_url_get(newURL, CURLUPART_URL, &result, 0);

    // Dump the result
    char *dump_result = strdup(result);

    // Deallocated
    free(result);
    free(language);
    free(query);

    curl_url_cleanup(newURL);

    return dump_result;
}

static unsigned int
memory_callback(void *content, unsigned int size, unsigned int nmemb, void *userp)
{
    struct Response *response = (struct Response *)userp;
    unsigned int realsize = size * nmemb;
    response->data = realloc(response->data, response->size + realsize + 1);
    if (response->data == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    memcpy(&(response->data[response->size]), content, realsize);
    response->size += realsize;
    response->data[response->size] = 0;

    return realsize;
}

char*
https_request(const char *query)
{
    //char *url = set_url("en_US", "Sunflower Lyric");
    char *url = set_url(get_os_lang(), query);
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
        /*
        else
            fprintf(stderr, "Response\n%s\n", response.data);
            */

        dump_response = strdup(response.data);

        curl_easy_cleanup(curl);
        free(response.data);
        free(url);
    }

    return dump_response;
}