
#ifndef UPDATER_INTERFACE_H
#define UPDATER_INTERFACE_H

#include "updater.h"

typedef void* UPDATER_PTR;

#if defined _MSC_FULL_VER 
extern "C" _declspec(dllexport)  UPDATER_PTR getUpdaterInstance();
extern "C" _declspec(dllexport)  void setCurrentVersion(UPDATER_PTR updater, const char* val, size_t len);
extern "C" _declspec(dllexport)  void getCurrentVersion(UPDATER_PTR updater, char* val, size_t len);
extern "C" _declspec(dllexport)  size_t getNextVersionAttribute(UPDATER_PTR updater, char * out, size_t outLen, const char * attribute, size_t attributeLen);
extern "C" _declspec(dllexport)  void findNextVersion(UPDATER_PTR updater);
extern "C" _declspec(dllexport)  void setInfoUrl(UPDATER_PTR updater, const char* val, size_t len);
extern "C" _declspec(dllexport)  void getInfoUrl(UPDATER_PTR updater, char* val, size_t len);
extern "C" _declspec(dllexport)  void setChannel(UPDATER_PTR updater, const char* val, size_t len);
extern "C" _declspec(dllexport)  void getChannel(UPDATER_PTR updater, char* val, size_t len);
extern "C" _declspec(dllexport)  void setAutoUpdateInterval(UPDATER_PTR updater, size_t hours);
extern "C" _declspec(dllexport)  void setAutoUpdateInterval(UPDATER_PTR updater, size_t hours);
extern "C" _declspec(dllexport)  void downloadInfo(UPDATER_PTR updater);
extern "C" _declspec(dllexport)  void downloadUpdate(UPDATER_PTR updater);
extern "C" _declspec(dllexport)  void checkSignature(UPDATER_PTR updater);
extern "C" _declspec(dllexport)  void runInstaller(UPDATER_PTR updater);
extern "C" _declspec(dllexport)  void setOperationResultEvent(UPDATER_PTR updater, OperationResultFunction handler);
#else
UPDATER_PTR getUpdaterInstance();
void setCurrentVersion(UPDATER_PTR updater, const char* val, size_t len);
void getCurrentVersion(UPDATER_PTR updater, char* val, size_t len);
size_t getNextVersionAttribute(UPDATER_PTR updater, char * out, size_t outLen, const char* attribute, size_t attributeLen);
void findUpdateVersion(UPDATER_PTR updater);
void setInfoUrl(UPDATER_PTR updater, const char* val, size_t len);
void getInfoUrl(UPDATER_PTR updater, char* val, size_t len);
void setChannel(UPDATER_PTR updater, const char* val, size_t len);
void getChannel(UPDATER_PTR updater, char* val, size_t len);
void setAutoUpdateInterval(UPDATER_PTR updater, size_t hours);
void setAutoUpdateInterval(UPDATER_PTR updater, size_t hours);
void downloadInfo(UPDATER_PTR updater);
void downloadUpdate(UPDATER_PTR updater);
void checkSignature(UPDATER_PTR updater);
void runInstaller(UPDATER_PTR updater);
void setOperationResultEvent(UPDATER_PTR updater, OperationResultFunction handler);
#endif


#endif // MTREPORTLIBH