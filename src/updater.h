
#ifndef UPDATER_H
#define UPDATER_H

#include <wchar.h>
#include <string>

struct VersionInfo
{
    unsigned long high;
    unsigned long low;
    unsigned long release;
    unsigned long build;

    VersionInfo():high(0), low(0), release(0), build(0) {}

    const std::wstring ToString() const; 
};

class Updater
{
public:
    Updater() {};
    ~Updater() {};

    const std::wstring getCurrentVersion() const;
    void setCurrentVersion(const VersionInfo & versionInfo);
    std::wstring getVersionInfoUrl() const;
    void setVersionInfoUrl(const char* url);
    void checkForUpdate() const;
private:
    std::wstring m_infoUrl;
    VersionInfo m_verInfo; 
};

#endif //UPDATER_H
