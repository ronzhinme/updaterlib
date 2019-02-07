
#include <stdio.h>
#include "updater.h"

std::wstring VersionInfo::ToString() const
{
    wchar_t buf[100];
    snwprintf(buf, 100, L"%ls.%ls.%ls.%ls", major, minor, release, build);
    return buf;
}

std::wstring Updater::getCurrentVersion() const
{
    return m_verInfo.ToString();
}
