
#ifndef UPDATER_INTERFACE_H
#define UPDATER_INTERFACE_H

#include "updater.h"

#if !defined(DLL_EXPORT)
#if defined _MSC_FULL_VER
#define DLL_EXPORT __declspec(dllexport)
#else 
#define DLL_EXPORT
#endif
#endif

typedef void *UPDATER_PTR;

extern "C"
{
    DLL_EXPORT UPDATER_PTR getUpdaterInstance();
    DLL_EXPORT void setCurrentVersion(UPDATER_PTR updater, const char *val, size_t len);
    DLL_EXPORT void getCurrentVersion(UPDATER_PTR updater, char *val, size_t len);
    DLL_EXPORT size_t getNextVersionAttribute(UPDATER_PTR updater, char *out, size_t outLen, const char *attribute, size_t attributeLen);
    DLL_EXPORT void findNextVersion(UPDATER_PTR updater);
    DLL_EXPORT void setInfoUrl(UPDATER_PTR updater, const char *val, size_t len);
    DLL_EXPORT void getInfoUrl(UPDATER_PTR updater, char *val, size_t len);
    DLL_EXPORT void setChannel(UPDATER_PTR updater, const char *val, size_t len);
    DLL_EXPORT void getChannel(UPDATER_PTR updater, char *val, size_t len);
    DLL_EXPORT void setAutoUpdateInterval(UPDATER_PTR updater, size_t hours);
    DLL_EXPORT void downloadInfo(UPDATER_PTR updater);
    DLL_EXPORT void downloadUpdate(UPDATER_PTR updater);
    DLL_EXPORT void checkSignature(UPDATER_PTR updater);
    DLL_EXPORT void runInstaller(UPDATER_PTR updater);
    DLL_EXPORT void setOperationResultEvent(UPDATER_PTR updater, OperationResultFunction handler);
    DLL_EXPORT void checkAndUpdate(UPDATER_PTR updater);
    DLL_EXPORT UpdaterState getCurrentState(UPDATER_PTR updater);
    DLL_EXPORT void stopOperation(UPDATER_PTR updater);
    DLL_EXPORT void pauseDownloading(UPDATER_PTR updater);
    DLL_EXPORT void resumeDownloading(UPDATER_PTR updater);
}
#endif // UPDATER_INTERFACE_H