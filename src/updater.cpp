
#include <stdio.h>
#include <wchar.h>
#include "updater.h"

VersionInfo::VersionInfo(const std::wstring &val)
{
    wprintf(L"--- %ls\n", val.c_str());

    auto wstr = val;
    for (std::wstring::const_iterator i = wstr.begin(); i != wstr.end(); ++i)
    {
        wprintf(L"= %lc\n", (wchar_t *)*i);
        if (*i == L'.')
        {
            wstr = wstr.replace(i, i + 1, L" ");
        }
    }
    
    wprintf(L"=== %ls\n", wstr.c_str());

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

const std::wstring Updater::getCurrentVersion() const
{
    return m_verInfo.toString();
}
