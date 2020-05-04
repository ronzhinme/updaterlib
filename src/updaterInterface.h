
#ifndef UPDATER_INTERFACE_H
#define UPDATER_INTERFACE_H

#include "updater.h"

typedef void *UPDATER_PTR;
#if defined _MSC_FULL_VER

#if !defined(DLL_EXPORT)
#define DLL_EXPORT __declspec(dllexport)
#endif
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
}
#else
UPDATER_PTR getUpdaterInstance();
void setCurrentVersion(UPDATER_PTR updater, const char *val, size_t len);
void getCurrentVersion(UPDATER_PTR updater, char *val, size_t len);
size_t getNextVersionAttribute(UPDATER_PTR updater, char *out, size_t outLen, const char *attribute, size_t attributeLen);
void findNextVersion(UPDATER_PTR updater);
void setInfoUrl(UPDATER_PTR updater, const char *val, size_t len);
void getInfoUrl(UPDATER_PTR updater, char *val, size_t len);
void setChannel(UPDATER_PTR updater, const char *val, size_t len);
void getChannel(UPDATER_PTR updater, char *val, size_t len);
void setAutoUpdateInterval(UPDATER_PTR updater, size_t hours);
void downloadInfo(UPDATER_PTR updater);
void downloadUpdate(UPDATER_PTR updater);
void checkSignature(UPDATER_PTR updater);
void runInstaller(UPDATER_PTR updater);
void setOperationResultEvent(UPDATER_PTR updater, OperationResultFunction handler);
void checkAndUpdate(UPDATER_PTR updater, bool askOnUpdate);
UpdaterState getCurrentState(UPDATER_PTR updater);
void stopOperation(UPDATER_PTR updater);
#endif

#endif // UPDATER_INTERFACE_H