
#ifndef CURL_BRIDGE_H
#define CURL_BRIDGE_H

#include <string>

class CurlBridge
{
  public:
    void downloadFileFromUrl(const std::wstring url);
    void openUrl(const std::wstring url);
};

#endif