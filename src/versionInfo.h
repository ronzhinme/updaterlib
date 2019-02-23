
#ifndef VERSION_INFO_H
#define VERSION_INFO_H

#include <string>

struct VersionInfo
{
    unsigned long high;
    unsigned long low;
    unsigned long release;
    unsigned long build;

    VersionInfo():high(0), low(0), release(0), build(0) {}
    VersionInfo(const std::wstring & val);
    const std::wstring toString() const; 
    bool less(const VersionInfo & vi) const;
};

#endif