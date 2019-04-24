
#ifndef CURL_BRIDGE_H
#define CURL_BRIDGE_H

#include <string>
#include <functional>

typedef std::function<void(const char*, size_t)> DataReceivedFunction;
typedef std::function<void()> DataReceivedFinisedFunction;
class CurlBridge 
{
public:
  bool getUrlData(const std::string &url);

  void onDataReceivedEvent(DataReceivedFunction handler);
  void onDataReceivedFinished(DataReceivedFinisedFunction handler);

  DataReceivedFunction onDataReceived() const;
  DataReceivedFinisedFunction onDataReceivedFinished() const;
private:
  DataReceivedFunction m_onDataReceived = NULL;
  DataReceivedFinisedFunction m_onDataFinished = NULL;
};

#endif