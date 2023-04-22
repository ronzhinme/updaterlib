
#ifndef UPDATER_H
#define UPDATER_H

#include <wchar.h>
#include <string>
#include <cstring>
#include <memory>
#include "versionInfo.h"
#include "curlBridge.h"
#include "xmlParser.h"
#include "extraInfo.h"

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
    void pauseDownloading();
    void resumeDownloading();
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
