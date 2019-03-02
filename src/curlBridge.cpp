
#include <curl/curl.h>
#include "curlBridge.h"

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    printf("%s\n", (char *)ptr);
    return size * nmemb;
}

bool CurlBridge::getUrlData(const std::string &url, std::wstring &data)
{
    if (url.empty())
        return false;

    CURL *curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl)
    {
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

    auto res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);

    curl_global_cleanup();
    return true;
}