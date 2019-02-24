
#include <curl/curl.h>
#include "curlBridge.h"

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

void CurlBridge::getUrlData(const std::wstring &url, std::wstring &data)
{
    if(url.empty())
        return;

    CURL *curl;
    static const char *pagefilename = "page.out";
    FILE *pagefile;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

    /* open the file */
    pagefile = fopen(pagefilename, "wb");
    if (pagefile)
    {

        /* write the page body to this file handle */
        curl_easy_setopt(curl , CURLOPT_WRITEDATA, pagefile);

        /* get it! */
        curl_easy_perform(curl);

        /* close the header file */
        fclose(pagefile);
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
}