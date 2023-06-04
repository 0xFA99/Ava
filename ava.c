#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml/HTMLparser.h>
#include <curl/curl.h>
#include <getopt.h>

#include "ava.h"

#include "config.h"
#include "utils.h"
#include "answer.h"

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

    curl_url_get(newURL, CURLUPART_URL, &result, 0);

    char *dump_result = strdup(result);

    free(language);
    free(query);

    curl_url_cleanup(newURL);

    return dump_result;
}

char*
https_request(const char *query)
{
	char *url = set_url("en_US", query);
	CURL *curl;
	CURLcode res;
	struct Response response;

	response.data = malloc(1024 * 1024);
	response.size = 0;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memory_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform, failed: %s\n", curl_easy_strerror(res));
			return NULL;
		}

		return response.data;
	}

	return NULL;
}

int
main(int argc, char *argv[])
{
	int opt;
        char *query = NULL;

	struct Flags SFlags = { false, false, false, false, false, false };
	struct option long_opts[] = {
			{ "raw",        no_argument, NULL, 'r' },
			{ "version",    no_argument, NULL, 'v' },
			{ "help",       no_argument, NULL, 'h' },
			{ "quiet",      no_argument, NULL, 'q' },
			{ "all",        no_argument, NULL, 'a' },
			{ "debug",      no_argument, NULL, 'd' },
			{ "save",       no_argument, NULL, 's' },
			{ "plus_urls",  no_argument, NULL, 'u' }
	};

	while ((opt = getopt_long(argc, argv, "rvhqadsu", long_opts, NULL)) != -1) {
		switch (opt) {
			case 'r':
				SFlags.raw = true; break;
			case 'v':
				die("AVA Version: %s\n", VERSION); return 1;
			case 'h':
				die(GREEN "Usage: " RESET "ava " YELLOW "[options] " RESET MAGENTA "\"query\"\n" RESET);
				return 1;
			case 'q':
				SFlags.quiet = true; break;
			case 'a':
				SFlags.all = true; break;
			case 'd':
				SFlags.debug = true; break;
			case 's':
				SFlags.save_html = true; break;
			case 'u':
				SFlags.plus_urls = true; break;
			case '?':
				die("Invalid option\n"); break;
			default:
				die("Unknown option\n"); break;
		}
	}

	if (argc > optind) {
		query = argv[argc - 1];
		if (strlen(query) == 0) {
			die("Query: (empty)\n");
			return 1;
		}
	}

        if (query == NULL) {
                die(GREEN "Usage: " RESET "ava " YELLOW "[options] " RESET MAGENTA "\"query\"\n" RESET);
                    return 1;
        }

    /*
     * OFFLINE
    FILE *file = fopen("/home/saputri/.cache/ava/12-10:12:21_ava.html", "r");

    if (file == NULL) return 1;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *response = malloc(file_size + 1);
    if (response == NULL) {
        fclose(file);
        return 1;
    }

    size_t bytes_read = fread(response, 1, file_size, file);
    if (bytes_read != file_size) {
        free(response);
        fclose(file);
        return 1;
    }

    response[file_size] = '\0';

    fclose(file);
     */

	char *response = NULL;

	if (SFlags.debug) {
            double response_time, parsing_time;
            struct timespec start_time, end_time;

            clock_gettime(CLOCK_REALTIME, &start_time);
            response = https_request(query);
            clock_gettime(CLOCK_REALTIME, &end_time);

            response_time = (double)(end_time.tv_sec - start_time.tv_sec) +
                            (double)(end_time.tv_nsec - start_time.tv_nsec) / 1e9;

            if (SFlags.save_html)
                    save_to_file(response);

            clock_gettime(CLOCK_REALTIME, &start_time);
            parse_html(SFlags, response);
            clock_gettime(CLOCK_REALTIME, &end_time);

            parsing_time = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_nsec - start_time.tv_nsec) / 1e9;

            printf("Response Time: %f\n", response_time);
            printf("Parsing Time: %f\n", parsing_time);
	} else {
            response = https_request(query);

            if (SFlags.save_html)
                    save_to_file(response);

            parse_html(SFlags, response);
	}

	free(response);

    return 0;
}
