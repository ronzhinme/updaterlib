#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <chrono>
#include <stdio.h>
#elif defined(__linux__)
#endif

#include "platformSpecific.h"

#if defined(_WIN32)
void runInstallerWindows(const std::string& filename, const std::string& argString)
{
    //system((filename + " " + argString).c_str());
    bool isNeedElevation = false;
    
    SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = isNeedElevation ? TEXT("runas") : TEXT("open");
	ShExecInfo.lpFile = filename.c_str();
	ShExecInfo.lpParameters = argString.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOWNORMAL;
	ShExecInfo.hInstApp = NULL;
	
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
}

#elif defined(__APPLE__)
void runInstallerMacOS(const std::string& filename, const std::string& argString)
{
    auto attachDir = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    const int cmdLength = 128;
    char attachImageCmd[cmdLength];
    char copyApplicationCmd[cmdLength];
    char detachImageCmd[cmdLength];

    memset(&attachImageCmd[0], 0, cmdLength);
    memset(&copyApplicationCmd[0], 0, cmdLength);
    memset(&detachImageCmd[0], 0, cmdLength);

    snprintf(&attachImageCmd[0], cmdLength, "/usr/bin/hdiutil attach -mountpoint /tmp/%lld %s", attachDir, filename.c_str());
    snprintf(&copyApplicationCmd[0], cmdLength, "find /tmp/%lld -name \\*.app -exec cp -fr {} /Applications/ \";\" ", attachDir);
    snprintf(&detachImageCmd[0], cmdLength, "/usr/bin/hdiutil detach /tmp/%lld", attachDir);

    system(attachImageCmd);
    system(copyApplicationCmd);
    system(detachImageCmd);
}

#elif defined(__linux__)
void runInstallerLinux(const std::string& filename, const std::string& argString)
{
    system((filename + " " + argString).c_str());
}
#endif

void PlatformSpecific::runInstaller(const std::string& filename, const std::string& argString)
{
#if defined(_WIN32)
    runInstallerWindows(filename, argString);
#elif defined(__APPLE__)
    runInstallerMacOS(filename, argString);
#elif defined(__linux__)
    runInstallerLinux(filename, argString);
#else
#endif
}