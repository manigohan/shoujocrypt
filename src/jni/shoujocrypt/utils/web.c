#include <stdio.h>
#include <curl/curl.h>

#include <web.h>

int post(const char *url, const char *data) {
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
 
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      fprintf(stderr, "post failed: %s\n", curl_easy_strerror(res));
      return 1;
    } else {
      return 0;
    };
    curl_easy_cleanup(curl);
};

int get(const char *url, long *status_code) {
    CURL *curl;
    CURLcode res;
    long response_code = 0;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_3);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "get failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            return -1;
        }

        // Get the status code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        *status_code = response_code;

        curl_easy_cleanup(curl);
        return 0;
    }

    return -1; // curl failed to init
}
