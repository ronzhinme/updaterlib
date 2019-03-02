
#ifndef CURL_BRIDGE_H
#define CURL_BRIDGE_H

#include <string>

class CurlBridge
{
  public:
    bool getUrlData(const std::string & url, std::wstring & data);
};

#endif