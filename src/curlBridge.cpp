
#include <curl/curl.h>
#include "curlBridge.h"

static size_t write_data(void *receivedData, size_t size, size_t nmemb, void *bridgePtr)
{
    size_t readBytesCount = size * nmemb;
    CurlBridge *bridge = (CurlBridge *)bridgePtr;
    
    if (bridge->onDataReceived() != NULL)
    {
        bridge->onDataReceived()((const char *)receivedData, readBytesCount);
    }
    return readBytesCount;
}

void CurlBridge::onDataReceivedEvent(std::function<void(const char*, size_t)> handler) 
{
    m_onDataReceived = handler;
}

DataReceivedFunction CurlBridge::onDataReceived() const
{
    return m_onDataReceived;
}

bool CurlBridge::getUrlData(const std::string &url)
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
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

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