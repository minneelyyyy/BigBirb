#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <concord/discord.h>

#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, char **s) {
    *s = malloc(size * nmemb + 1);

    memcpy(*s, ptr, size * nmemb);

    (*s)[size * nmemb] = 0;

    return size * nmemb;
}

char *nekos_life_get(const char *endpoint) {
    CURL *curl = curl_easy_init();
    CURLcode code;
    char url[1028];
    char *data = NULL;

    sprintf(url, "https://nekos.life/api/v2/img/%s", endpoint);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

    code = curl_easy_perform(curl);

    if (code != CURLE_OK) {
        log_warn("failed to connect (%s): %s", url, curl_easy_strerror(code));

        if (data != NULL) {
            free(data);
        }
    }

    curl_easy_cleanup(curl);

    return code == 0 ? data : NULL;
}
