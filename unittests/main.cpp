
#include "curl/curl.h"

int main(void) {
    CURLcode ret;
    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        exit(EXIT_FAILURE);
    }

    ret = curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
    if (ret != CURLE_OK) {
        exit(EXIT_FAILURE);
    }

    ret = curl_easy_perform(curl);
    if (ret != 0) { 
        exit(EXIT_FAILURE);
    }

    return 0;
}
