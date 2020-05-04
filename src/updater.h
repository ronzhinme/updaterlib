
#ifndef UPDATER_H
#define UPDATER_H

#include <wchar.h>
#include <string>
#include <cstring>
#include <memory>
#include "versionInfo.h"
#include "curlBridge.h"
#include "xmlParser.h"

enum Result
{
    RESULT_INPROGRESS,
    RESULT_SUCCESS,
    RESULT_FAILED,
    RESULT_CANCELED,
};

enum OperationType
{
    TYPE_DOWNLOAD_INFO,
    TYPE_DOWNLOAD_UPDATE,
    TYPE_CHECK_UPDATE_VERSION,
    TYPE_CHECK_SIGNATURE,
    TYPE_RUN_INSTALLER,
};

enum UpdaterState
{
    STATE_READY,
    STATE_CHECKING,
    STATE_DOWNLOADING,
    STATE_UPDATING,
};

#pragma pack(push, 1)
struct DownloadBytesInfo 
{
    size_t current;
    size_t total;
};
#pragma pack(pop)

struct ExtraInfo
{
    char *info;
    size_t infoLength;
    ExtraInfo() : info(NULL), infoLength(0) {}
    explicit ExtraInfo(const void *val, size_t len);
    ~ExtraInfo();
};

typedef std::function<void(OperationType, Result, const ExtraInfo &)> OperationResultFunction;

class Updater
{
  public:
    Updater();
    ~Updater(){};
    Updater(const Updater & src);
    Updater operator= (const Updater & src);

    VersionInfo versionInfo;
    VersionInfo updateVersionInfo;
    const std::string & getVersionInfoUrl() const;
    void setVersionInfoUrl(const std::string & url);
    const std:: string & getChannel() const;
    void setChannel(const std::string & channel);
    unsigned long getAutoUpdateInterval() const;
    void setAutoUpdateInterval(unsigned long hours);
    void downloadInfo();
    void findUpdateVersion();
    std::string getNextVersionAttribute(const std::string & attribute);
    void downloadUpdate();
    void checkUpdateSignature();
    void runInstaller();
    void onOperationResultEvent(OperationResultFunction handler);
    OperationResultFunction operationResult() const;
    void checkAndUpdate();
    UpdaterState getCurrentState();
    void stopOperation();
    bool isCheckAndUpdate();
  private:
    UpdaterState m_currentState;
    bool m_isCheckAndUpdate;
    std::string m_infoUrl;
    std::string m_channel;
    std::string m_xmlData;
    OperationResultFunction m_operationResult;
    unsigned long m_autoUpdateInterval;
    std::shared_ptr<CurlBridge> m_curlBridge;
    std::shared_ptr<XmlParser> m_xmlParser;
    DownloadBytesInfo m_downloadProgress;
    FILE* updateFile;
    void _appendDataToTempUpdateFile(const void * data, size_t dataSize);
    void _deleteTempUpdateFile();
    void _onDataReceived(OperationType operationType, const char *data, size_t dataSize);
    void _copyData(const Updater & src);
    bool _getSHA512FromUpdate(unsigned char * sha512Signature);
};

#endif //UPDATER_H
