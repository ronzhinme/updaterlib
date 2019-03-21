
#include <stdio.h>
#include <wchar.h>
#include <functional>

#include "updater.h"

using namespace std::placeholders;

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

unsigned long Updater::getAutoUpdateInterval() const
{
    return m_autoUpdateInterval;
}

void Updater::setAutoUpdateInterval(unsigned long hours)
{
    m_autoUpdateInterval = hours;
}

void Updater::onDataReceived(const char* data, size_t dataSize)
{
    printf("%s [%s] [%ld]\n", __FUNCTION__, (const char *)data, dataSize);
}

void Updater::checkForUpdate()
{
    const std::string url("http://www.example.com/");

    m_curlBridge.onDataReceivedEvent([this](const char* d, size_t l){this->onDataReceived(d,l);});
    m_curlBridge.getUrlData(url);

    // download signature (dSign)
    // download xml (xmlInfo)
    // calculate xml signature (cSign)
    // compare cSign and dSign
    // if diff return with errCode
    // parse xml
    // check if xml contains info about new version
    // return with okCode
}