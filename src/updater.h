
#ifndef UPDATER_H
#define UPDATER_H

#include <wchar.h>
#include <string>

struct VersionInfo
{
    unsigned long major;
    unsigned long minor;
    unsigned long release;
    unsigned long build;

    VersionInfo():major(0), minor(0), release(0), build(0) {}

    std::wstring ToString() const; 
};

class Updater
{
public:
    Updater() {};
    ~Updater() {};

    std::wstring getCurrentVersion() const;
    void setCurrentVersion(const VersionInfo & versionInfo);
    std::wstring getVersionInfoUrl() const;
    void setVersionInfoUrl(const char* url);
    void checkForUpdate() const;
private:
    std::wstring m_infoUrl;
    VersionInfo m_verInfo; 
};

#endif //UPDATER_H
