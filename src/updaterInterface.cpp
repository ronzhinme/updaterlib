#include <string.h>
#include <thread>
#include "updaterInterface.h"

UPDATER_PTR getUpdaterInstance()
{
    return new Updater();
}

void setCurrentVersion(UPDATER_PTR updater, const char *val, size_t len)
{
    ((Updater *)updater)->versionInfo = VersionInfo(val, len);
}

void getCurrentVersion(UPDATER_PTR updater, char *val, size_t len)
{
    auto data = ((Updater *)updater)->versionInfo.toString();
    if (data.length() > len)
        return;

    memcpy(val, data.c_str(), data.length());
}

size_t getNextVersionAttribute(UPDATER_PTR updater, char *out, size_t outLen, const char *attribute, size_t attributeLen)
{

    auto data = ((Updater *)updater)->getNextVersionAttribute(std::string(attribute, attributeLen));

    if (data.length() > outLen)
        memcpy(out, data.c_str(), outLen);

    memcpy(out, data.c_str(), data.length());

    return data.length();
}

void findNextVersion(UPDATER_PTR updater)
{
    ((Updater *)updater)->findUpdateVersion();
}

void setInfoUrl(UPDATER_PTR updater, const char *val, size_t len)
{
    auto versionInfo(std::string(val, len));
    ((Updater *)updater)->setVersionInfoUrl(versionInfo);
}

void getInfoUrl(UPDATER_PTR updater, char *val, size_t len)
{
    auto data = ((Updater *)updater)->getVersionInfoUrl();
    if (data.length() > len)
        return;

    memcpy(val, data.c_str(), data.length());
}

void setChannel(UPDATER_PTR updater, const char *val, size_t len)
{
    const char *v = val;
    ((Updater *)updater)->setChannel(std::string(v, len));
}

void getChannel(UPDATER_PTR updater, char *val, size_t len)
{
    auto data = ((Updater *)updater)->getChannel();
    if (data.length() > len)
        return;

    memcpy(val, data.c_str(), data.length());
}

void setAutoUpdateInterval(UPDATER_PTR updater, size_t hours)
{
    ((Updater *)updater)->setAutoUpdateInterval(hours);
}

void downloadInfo(UPDATER_PTR updater)
{
    ((Updater *)updater)->downloadInfo();
}

void downloadUpdate(UPDATER_PTR updater)
{
    ((Updater *)updater)->downloadUpdate();
}

void checkSignature(UPDATER_PTR updater)
{
    ((Updater *)updater)->checkUpdateSignature();
}

void runInstaller(UPDATER_PTR updater)
{
    ((Updater *)updater)->runInstaller();
}

void setOperationResultEvent(UPDATER_PTR updater, OperationResultFunction handler)
{
    ((Updater *)updater)->onOperationResultEvent(handler);
}

void checkAndUpdate(UPDATER_PTR updater)
{
    ((Updater *)updater)->checkAndUpdate();
}

UpdaterState getCurrentState(UPDATER_PTR updater)
{
    return ((Updater *)updater)->getCurrentState();
}

void stopOperation(UPDATER_PTR updater)
{
    ((Updater *)updater)->stopOperation();
}