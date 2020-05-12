
#include "curlBridge.h"
#include <curl/curl.h>

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

CurlBridge::CurlBridge()
{
    m_curl = NULL;
}

void CurlBridge::onDataReceivedEvent(std::function<void(const char *, size_t)> handler)
{
    m_onDataReceived = handler;
}

void CurlBridge::onDataReceivedFinished(std::function<void()> handler)
{
    m_onDataFinished = handler;
}

DataReceivedFunction CurlBridge::onDataReceived() const
{
    return m_onDataReceived;
}

DataReceivedFinisedFunction CurlBridge::onDataReceivedFinished() const
{
    return m_onDataFinished;
}

bool CurlBridge::getUrlData(const std::string &url)
{
    if (url.empty())
        return false;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    m_curl = curl_easy_init();
    if (!m_curl)
    {
        return false;
    }

    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);

    auto res = curl_easy_perform(m_curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    else
    {
        if (m_onDataFinished != NULL)
            onDataReceivedFinished()();
    }

    curl_easy_cleanup(m_curl);
    curl_global_cleanup();

    return true;
}

void CurlBridge::pauseDownloading()
{
    curl_easy_pause(m_curl, CURLPAUSE_ALL);
}

void CurlBridge::resumeDownloading()
{
    curl_easy_pause(m_curl, CURLPAUSE_CONT);
}