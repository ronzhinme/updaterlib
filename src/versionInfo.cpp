
#include "versionInfo.h"

VersionInfo::VersionInfo(const std::wstring &val)
{
    auto wstr = val;
    for (std::wstring::iterator i = wstr.begin(); i != wstr.end(); ++i)
    {
        if (*i == L'.')
        {
            wstr = wstr.replace(i, i + 1, L" ");
        }
    }
    
    wchar_t *pEnd;
    high = wcstoul(wstr.c_str(), &pEnd, 10);
    low = wcstoul(pEnd, &pEnd, 10);
    release = wcstoul(pEnd, &pEnd, 10);
    build = wcstoul(pEnd, &pEnd, 10);
}

const std::wstring VersionInfo::toString() const
{
    return std::to_wstring(high) + L"." + std::to_wstring(low) + L"." + std::to_wstring(release) + L"." + std::to_wstring(build);
}

bool VersionInfo::less(const VersionInfo & vi) const
{
    return high < vi.high || 
            (high == vi.high && low < vi.low) || 
            (high == vi.high && low == vi.low && release < vi.release) ||
            (high == vi.high && low == vi.low && release == vi.release && build < vi.build);
}