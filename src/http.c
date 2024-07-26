
#include "ava.h"
#include "utils.h"
#include "http.h"

#include <string.h>
#include <curl/curl.h>

#define MAX_LINK 127
#define BARE_URL "https://www.google.com/search?hl=US_en&q="

const char user_agent[] = "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) QtWebEngine/5.15.2 Chrome/87.0.4280.144 Safari/537.36";

static size_t
write_callback(char *data, size_t size, size_t nmemb, void *clientp)
{
    size_t realsize = size*nmemb;
    struct Response *response = (struct Response *)clientp;

    char *ptr = (char *)realloc(response->data, response->size + realsize + 1);
    if (ptr == NULL) return 0;

    response->data = ptr;
    memcpy(&(response->data[response->size]), data, realsize);
    response->size += realsize;
    response->data[response->size] = 0;

    return realsize;
}

void
send_http_request(struct Ava *ava)
{
    char url[MAX_LINK] = { 0 };

    snprintf(url, MAX_LINK, "%s%s", BARE_URL, url_encode(ava->query));

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)ava->response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "[ERROR] Failed curl performance: %s\n",
                    curl_easy_strerror(res));
                    
            free(ava->response->data);
            ava->response->data = NULL;
        }

    } else {
        fprintf(stderr, "[ERROR] Failed to initialize CURL.\n");
    }

    curl_easy_cleanup(curl);
}

