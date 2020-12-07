
#include <string>

#if defined(_WIN32)
const std::string UPDATE_FILENAME = "temp.upd.exe";
#elif defined(__APPLE__)
const std::string UPDATE_FILENAME = "temp.upd.dmg";
#elif defined(__linux__)
const std::string UPDATE_FILENAME = "temp.upd.AppImage";
#else
const std::string UPDATE_FILENAME = "temp.upd.dat";
#endif

namespace PlatformSpecific
{
    void runInstaller(const std::string & filename, const std::string & argString);
}