
#ifndef VERSION_INFO_H
#define VERSION_INFO_H

#include <string>

class VersionInfo
{
public:
    unsigned long high;
    unsigned long low;
    unsigned long release;
    unsigned long build;

    VersionInfo();
    ~VersionInfo();
    VersionInfo(const std::string & val);
    VersionInfo(const char* val, size_t valLen);
    VersionInfo(const VersionInfo& src);
    VersionInfo & operator = (const VersionInfo & src);

    std::string && toString(); 
    int compare(const VersionInfo & vi) const;
    
private:
    std::string m_VersionString;
    std::string getVersionString() const;
    void _copyData(const VersionInfo & src);
    void _fromString(const std::string & val);
};

#endif