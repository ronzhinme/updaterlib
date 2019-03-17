
#ifndef CURL_BRIDGE_H
#define CURL_BRIDGE_H

#include <string>
#include <functional>

typedef std::function<void(const char*, size_t)> DataReceivedFunction;

class CurlBridge 
{
public:
  bool getUrlData(const std::string &url);

  void onDataReceivedEvent(DataReceivedFunction handler);
  DataReceivedFunction onDataReceived() const;
private:
  DataReceivedFunction m_onDataReceived = NULL;
};

#endif