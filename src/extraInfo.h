#ifndef EXTRAINFO_H
#define EXTRAINFO_H

#include <functional>

enum UpdaterState
{
    STATE_READY,
    STATE_CHECKING,
    STATE_DOWNLOADING,
    STATE_UPDATING,
    STATE_PAUSED,
};

enum OperationType
{
    TYPE_DOWNLOAD_INFO,
    TYPE_DOWNLOAD_UPDATE,
    TYPE_CHECK_UPDATE_VERSION,
    TYPE_CHECK_SIGNATURE,
    TYPE_RUN_INSTALLER,
};

enum Result
{
    RESULT_INPROGRESS,
    RESULT_SUCCESS,
    RESULT_FAILED,
    RESULT_CANCELED,
};

struct ExtraInfo
{
    char *info;
    size_t infoLength;
    ExtraInfo() : info(nullptr), infoLength(0) {}
    explicit ExtraInfo(const void *val, size_t len);
    ~ExtraInfo();
};

#pragma pack(push, 1)
struct DownloadBytesInfo 
{
    size_t current;
    size_t total;
};
#pragma pack(pop)

typedef std::function<void(OperationType, Result, const ExtraInfo &)> OperationResultFunction;

#endif