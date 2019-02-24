
#ifndef CURL_BRIDGE_H
#define CURL_BRIDGE_H

#include <string>

class CurlBridge
{
  public:
    void getUrlData(const std::wstring & url, std::wstring & data);
};

#endif