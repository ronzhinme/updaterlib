
#ifndef UPDATER_H
#define UPDATER_H

#include <wchar.h>
#include <string>

#include "versionInfo.h"
#include "curlBridge.h"

class Updater
{
public:
    Updater() {};
    ~Updater() {};

    const std::wstring getCurrentVersion() const;
    void setCurrentVersion(const VersionInfo & versionInfo);
    std::wstring getVersionInfoUrl() const;
    void setVersionInfoUrl(const wchar_t* url);
    void checkForUpdate();
    unsigned long getAutoUpdateInterval() const;
    void setAutoUpdateInterval(unsigned long hours);
private:
    std::wstring m_infoUrl;
    VersionInfo m_verInfo; 
    unsigned long m_autoUpdateInterval;
    CurlBridge m_curlBridge;
    void onDataReceived(const char* data, size_t dataSize);
};

#endif //UPDATER_H
