
#include <stdio.h>
#include <wchar.h>
#include "updater.h"

const std::wstring Updater::getCurrentVersion() const
{
    return m_verInfo.toString();
}

void Updater::setCurrentVersion(const VersionInfo & versionInfo)
{
    m_verInfo.operator=(versionInfo);
}

void  Updater::setVersionInfoUrl(const wchar_t* url)
{
    m_infoUrl.clear();
    m_infoUrl.assign(url);
}

std::wstring Updater::getVersionInfoUrl() const
{
    return m_infoUrl.c_str();
}

void Updater::checkForUpdate() const
{

}