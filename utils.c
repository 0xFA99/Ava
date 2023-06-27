#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <iconv.h>
#include <unistd.h>

#include <sys/stat.h>

#include "utils.h"
#include "answer.h"

void
exitWithError(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    if (fmt[0] && fmt[strlen(fmt) - 1] == ':') {
        fputc(' ', stderr);
        perror(NULL);
    } else {
        fputc('\n', stderr);
    }

    exit(1);
}

char*
getCacheDirectory(void)
{
	char* cache_dir = getenv("XDG_CACHE_HOME");
	if (!cache_dir || !cache_dir[0]) {
		char* home_dir = getenv("HOME");
		if (!home_dir || !home_dir[0]) {
			fprintf(stderr, "Can't access home directory!\n");
			return NULL;
		}

		size_t len = strnlen(home_dir, PATH_MAX) + strlen("/.cache/") + strlen("ava") + 1;
		cache_dir = malloc(len);
		if (!cache_dir) {
			fprintf(stderr, "Memory allocation failed!\n");
			return NULL;
		}

		snprintf(cache_dir, len, "%s/.cache/%s", home_dir, "ava");
	}

	struct stat st;
	if (stat(cache_dir, &st) == 0) {
		if (!S_ISDIR(st.st_mode)) {
			fprintf(stderr, "Cache path is not a directory!\n");
			free(cache_dir);
			return NULL;
		}
		if (access(cache_dir, W_OK) != 0) {
			fprintf(stderr, "No write permissions in the cache directory!\n");
			free(cache_dir);
			return NULL;
		}
	} else if (errno != ENOENT) {
		perror("Error accessing cache directory");
		free(cache_dir);
		return NULL;
	} else {
		if (mkdir(cache_dir, 0755) != 0 && errno != EEXIST) {
			perror("Error creating cache directory");
			free(cache_dir);
			return NULL;
		}
	}

	return cache_dir;
}

char*
convertLatin1ToUtf8(const char *iso8859_1_str)
{
    size_t iso8859_1_len = strlen(iso8859_1_str);
    size_t utf8_len = iso8859_1_len * 4;
    char *utf8_str = (char *)malloc(utf8_len);

    iconv_t conv = iconv_open("UTF-8", "ISO-8859-1");
    
    if (conv == (iconv_t)(1)) {
        exit(1);
    }

    char *in_buf = (char *)iso8859_1_str;
    char *out_buf = utf8_str;
    size_t in_len = iso8859_1_len;
    size_t out_len = utf8_len;

    if (iconv(conv, &in_buf, &in_len, &out_buf, &out_len) == (size_t)(-1)) {
        exit(1);
    }

    iconv_close(conv);
    utf8_str[utf8_len - out_len] = '\0';

    return utf8_str;
}

void
saveResponseToFile(const char *response)
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%d-%T_ava", timeinfo);

    char filename[100];
    char *cache_dir = getCacheDirectory();
    snprintf(filename, 100, "%s/%s.html", cache_dir, buffer);

    free(cache_dir);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    fprintf(file, "%s", response);
    printf("File saved in \'%s\'\n", filename);
    fclose(file);
}

void
printSingleResult(bool raw, const char *result)
{
    if (raw) {
        printf("%s\n", result);
    } else {
        puts(GREEN "-----" RESET);
        printf("%s\n", result);
        puts(GREEN "-----" RESET);
    }
}

void
printResultList(bool number, bool raw, int limit, xmlChar **content)
{
	int size = 0;

	if (limit == 0) {
		while (content[size] != NULL) {
			size++;
		}
	} else {
		size = limit;
	}

	if (raw) { printf(GREEN "-----" RESET); }

	for (int i = 0; i < size; i++) {
		if (number) {
			printf("%d. %s\n", i + 1, (const char *) content[i]);
		} else {
			printf("%s\n", (const char *) content[i]);
		}
	}

	if (raw) { printf(GREEN "-----" RESET); }
}

void
printMultiList(bool number, bool raw, bool horizontal, int limit, xmlChar **content, xmlChar **content2)
{
	int size = limit;

	if (limit == 0) {
		while (content[size] != NULL) size++;
	}

	if (raw) { printf(GREEN "-----" RESET); }

	for (int i = 0; i < size; i++) {
		if (number) {
			if (horizontal) {
				printf("%d. %s: %s\n", i + 1, (const char *) content[i], (const char *) content2[i]);
			} else {
				printf("%d. %s\n    %s\n", i + 1, (const char *) content[i], (const char *) content2[i]);
			}
		} else {
			if (horizontal) {
				printf("%s: %s\n", (const char *) content[i], (const char *) content2[i]);
			} else {
				printf("%s\n    %s\n", (const char *) content[i], (const char *) content2[i]);
			}
		}
	}

	if (raw) { printf(GREEN "-----" RESET); }
}

void
printNoResult(bool raw)
{
    if (raw) {
        puts("No Result!");
    } else {
        puts(GREEN "-----" RESET);
        puts("No Result!");
        puts(GREEN "-----" RESET);
    }
}

void
getCurrentTime(struct timespec *time)
{
	clock_gettime(CLOCK_REALTIME, time);
}

void
freeXmlCharList(xmlChar **contentList)
{
	int size = 0;
	while (contentList[size] != NULL) {
		xmlFree(contentList[size]);
		size++;
	}

	free(contentList);
}

void
freeXmlChar(xmlChar *content)
{
	xmlFree(content);
}
