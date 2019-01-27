
#ifndef UPDATER_H
#define UPDATER_H

#include <string>

struct VersionInfo
{
    unsigned long major;
    unsigned long minor;
    unsigned long release;
    unsigned long build;
};

class Updater
{
public:
    Updater();
    ~Updater();

    void setCurrentVersion(const VersionInfo & versionInfo);
    
    void setInfoUrl(const char* url);

private:
    std::string m_infoUrl;
    VersionInfo m_verInfo; 
};

#endif //UPDATER_H
