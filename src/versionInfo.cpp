
#include "versionInfo.h"
#include <iostream>
#include <algorithm>

VersionInfo::~VersionInfo()
{
}

VersionInfo::VersionInfo()
    : high(0), low(0), release(0), build(0)
{
}

std::string getStringRef(const std::string val)
{
    return val;
}

VersionInfo::VersionInfo(const std::string & val)
{
    _fromString(val);
}

VersionInfo::VersionInfo(const char *val, size_t valLen)
{
    _fromString(std::string(val, valLen));
}

VersionInfo::VersionInfo(const VersionInfo &src)
{
    _copyData(src);
}

std::string VersionInfo::getVersionString() const
{
    return m_VersionString;
}

std::string VersionInfo::toString()
{
    m_VersionString = std::to_string(high) + "." + std::to_string(low) + "." + std::to_string(release) + "." + std::to_string(build);
    return getVersionString();
}

int VersionInfo::compare(const VersionInfo &vi) const
{
    if (high == vi.high && low == vi.low && release == vi.release && build == vi.build)
        return 0;

    if (high < vi.high ||
        (high == vi.high && low < vi.low) ||
        (high == vi.high && low == vi.low && release < vi.release) ||
        (high == vi.high && low == vi.low && release == vi.release && build < vi.build))
        return -1;

    if (high > vi.high ||
        (high == vi.high && low > vi.low) ||
        (high == vi.high && low == vi.low && release > vi.release) ||
        (high == vi.high && low == vi.low && release == vi.release && build > vi.build))
        return 1;
}

VersionInfo &VersionInfo::operator=(const VersionInfo &src)
{
    _copyData(src);
    return *this;
}

void VersionInfo::_copyData(const VersionInfo &src)
{
    this->high = src.high;
    this->low = src.low;
    this->release = src.release;
    this->build = src.build;
}

void VersionInfo::_fromString(const std::string & val)
{
    std::string str(std::move(val));
    std::replace(str.begin(), str.end(), '.', ' ');

    char *pEnd;
    high = strtoul(str.c_str(), &pEnd, 10);
    low = strtoul(pEnd, &pEnd, 10);
    release = strtoul(pEnd, &pEnd, 10);
    build = strtoul(pEnd, &pEnd, 10);
}