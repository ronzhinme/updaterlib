
#ifndef UPDATER_H
#define UPDATER_H

#include <wchar.h>
#include <string>
#include <cstring>

#include "versionInfo.h"
#include "curlBridge.h"

enum Result
{
    RESULT_INPROGRESS,
    RESULT_SUCCESS,
    RESULT_FAILED,
    RESULT_CANCELED,
};

enum OperationType
{
    TYPE_CHECK,
    TYPE_DOWNLOAD,
};

struct ExtraInfo
{
    char *info;
    size_t infoLength;
    ExtraInfo() : info(NULL), infoLength(0) {}
    explicit ExtraInfo(const char *val, size_t len) : info(NULL), infoLength(0)
    {
        if (val == NULL)
            return;

        infoLength = len;
        info = new char[infoLength];
        memcpy(info, val, infoLength);
    }
};

typedef std::function<void(OperationType, Result, const ExtraInfo &)> OperationResultFunction;

class Updater
{
  public:
    Updater(){};
    ~Updater(){};

    const std::wstring getCurrentVersion() const;
    void setCurrentVersion(const VersionInfo &versionInfo);
    std::wstring getVersionInfoUrl() const;
    void setVersionInfoUrl(const wchar_t *url);
    unsigned long getAutoUpdateInterval() const;
    void setAutoUpdateInterval(unsigned long hours);
    void checkForUpdate();
    void downloadUpdate();
    void runInstaller();

    void onOperationResultEvent(OperationResultFunction handler);
    OperationResultFunction operationResult() const;

  private:
    std::wstring m_infoUrl;
    VersionInfo m_verInfo;
    unsigned long m_autoUpdateInterval;
    CurlBridge m_curlBridge;
    std::string m_xmlData;
    void onDataReceived(const char *data, size_t dataSize);
    OperationResultFunction m_operationResult;
};

#endif //UPDATER_H
