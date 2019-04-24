
#include <stdio.h>
#include <wchar.h>
#include <functional>

#include "updater.h"

using namespace std::placeholders;

const std::wstring Updater::getCurrentVersion() const
{
    return m_verInfo.toString();
}

void Updater::setCurrentVersion(const VersionInfo &versionInfo)
{
    m_verInfo.operator=(versionInfo);
}

void Updater::setVersionInfoUrl(const wchar_t *url)
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

void Updater::onDataReceived(const char *data, size_t dataSize)
{
    printf("%s [%s] [%ld]\n", __FUNCTION__, (const char *)data, dataSize);
}

void Updater::checkForUpdate()
{
    const std::string url("https://bitbucket.org/ronmih/appupdaterlib/src/master/unittests/appUpdateSample.xml");

    m_curlBridge.onDataReceivedEvent([this](const char *d, size_t l) { this->onDataReceived(d, l); });
    m_curlBridge.getUrlData(url);

    // find in XML first update candidate (first cirtical or highest version) - the intaller url and sign-code

    if (m_operationResult != NULL)
    {
        printf("%s [%d] [%d]\n", __FUNCTION__, TYPE_CHECK, RESULT_SUCCESS);
        operationResult()(TYPE_CHECK, RESULT_SUCCESS, ExtraInfo());
    }

    return;

    // download installer
    // check
    // download signature (dSign)
    // download xml (xmlInfo)
    // calculate xml signature (cSign)
    // compare cSign and dSign
    // if diff return with errCode
    // parse xml
    // check if xml contains info about new version
    // return with okCode
}

void Updater::downloadUpdate()
{
    
    if (m_operationResult != NULL)
    {
        printf("%s [%d] [%d]\n", __FUNCTION__, TYPE_DOWNLOAD, RESULT_SUCCESS);
        operationResult()(TYPE_DOWNLOAD, RESULT_SUCCESS, ExtraInfo());
    }

    return;
}

void Updater::runInstaller()
{

}

void Updater::onOperationResultEvent(OperationResultFunction handler)
{
    m_operationResult = handler;
}

OperationResultFunction Updater::operationResult() const
{
    return m_operationResult;
}