#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libxml2/libxml/HTMLparser.h>
#include <curl/curl.h>
#include <getopt.h>

#include "ava.h"

#include "config.def.h"
#include "utils.h"
#include "answer.h"

unsigned int
handleMemoryCallback(void *content, size_t size, size_t nmemb, void *userp)
{
	struct HttpResponse *response = (struct HttpResponse *) userp;
	size_t realsize = size * nmemb;
	char *new_data = realloc(response->responseData, response->responseSize + realsize + 1);
	if (new_data == NULL) {
		fprintf(stderr, "Out of Memory!\n");
		return 0;
	}

	response->responseData = new_data;
	memcpy(&(response->responseData[response->responseSize]), content, realsize);
	response->responseSize += realsize;
	response->responseData[response->responseSize] = '\0';

	return realsize;
}

char*
createURL(const char *lang, const char *text)
{
	unsigned int lang_len = strlen("hl=") + strlen(lang);
	unsigned int text_len = strlen("q=") + strlen(text);
	char *language	= malloc(lang_len + 1);
	char *query		= malloc(text_len + 1);

	snprintf(language, lang_len + 1, "%s%s", "hl=", lang);
	snprintf(query, text_len + 1, "%s%s", "q=", text);

	CURLU *newURL = curl_url();
	curl_url_set(newURL, CURLUPART_SCHEME, "https", 0);
	curl_url_set(newURL, CURLUPART_URL, defaultSearchEngineUrl, 0);
	curl_url_set(newURL, CURLUPART_PATH, "search", 0);
	curl_url_set(newURL, CURLUPART_QUERY, language, CURLU_APPENDQUERY);
	curl_url_set(newURL, CURLUPART_QUERY, query, CURLU_APPENDQUERY | CURLU_URLENCODE);

	char *result = NULL;
	curl_url_get(newURL, CURLUPART_URL, &result, 0);

	char *dump_result = strdup(result);

	free(language);
	free(query);

	curl_url_cleanup(newURL);

	return dump_result;
}

char*
sendHttpsRequest(const char *query)
{
	char *defaultURL = createURL("en_US", query);
	CURL *curl;
	CURLcode res;
	struct HttpResponse response;

	response.responseData = malloc(1024 * 1024);
	response.responseSize = 0;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, defaultURL);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, defaultUserAgent);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform, failed: %s\n", curl_easy_strerror(res));
			free(response.responseData);
			response.responseData = NULL;
		}

		curl_easy_cleanup(curl);
	}

	free(defaultURL);

	return response.responseData;
}

int
main(int argc, char *argv[])
{
	char *query = NULL;

	struct SearchFlags SFlags = { 
		.raw		= false,
		.quiet		= false,
		.all		= false,
		.debug		= false,
		.save_html	= false,
		.plus_urls	= false
	};
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

	int opt;
	while ((opt = getopt_long(argc, argv, "rvhqadsu", long_opts, NULL)) != -1) {
		switch (opt) {
			case 'r':
				SFlags.raw = true; break;
			case 'v':
				exitWithError("AVA Version: %s\n", VERSION); return 1;
			case 'h':
				exitWithError(GREEN "Usage: " RESET "ava " YELLOW "[options] " RESET MAGENTA "\"query\"\n" RESET);
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
				exitWithError("Invalid option\n"); break;
			default:
				exitWithError("Unknown option\n"); break;
		}
	}

	if (optind < argc) {
		query = argv[optind];
		if (strlen(query) == 0) {
			exitWithError("Query: (empty)\n");
			return 1;
		}
	} else {
		exitWithError(GREEN "Usage: " RESET "ava " YELLOW "[options] " MAGENTA "\"query\"\n" RESET);
		return 1;
	}

	char *response = NULL;

	if (SFlags.debug) {
		struct timespec start_time, end_time;
		double response_time, parsing_time;

		getCurrentTime(&start_time);
		response = sendHttpsRequest(query);
		getCurrentTime(&end_time);

		response_time = (double)(end_time.tv_sec - start_time.tv_sec) +
						(double)(end_time.tv_nsec - start_time.tv_nsec) / 1e9;

		if (SFlags.save_html)
			saveResponseToFile(response);

		getCurrentTime(&start_time);
		parseHTML(SFlags, response);
		getCurrentTime(&end_time);

		parsing_time = (double)(end_time.tv_sec - start_time.tv_sec) +
					   (double)(end_time.tv_nsec - start_time.tv_nsec) / 1e9;

		printf("Response Time: %.3fs\n", response_time);
		printf("Parsing Time: %.3fs\n", parsing_time);
	} else {
		response = sendHttpsRequest(query);

		if (SFlags.save_html)
			saveResponseToFile(response);

		parseHTML(SFlags, response);
	}

	free(response);

    return 0;
}
