
#include <stdio.h>
#include "updater.h"

const std::wstring VersionInfo::ToString() const
{
    return std::to_wstring(major) + L"." + std::to_wstring(minor) + L"." + std::to_wstring(release) + L"." + std::to_wstring(build);
}

const std::wstring Updater::getCurrentVersion() const
{
    return m_verInfo.ToString();
}
