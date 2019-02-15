
#include <cstdlib>
#include <ctime>
#include "../src/updater.h"

bool compareVersion(const VersionInfo &vi, const std::wstring &val)
{
    if (vi.ToString().compare(val) != 0)
    {
        wprintf(L"%ls %ls\n", vi.ToString().c_str(), val.c_str());
        return false;
    }
    return true;
}

int main()
{
    VersionInfo vi;
    auto v = vi.ToString();

    if (!compareVersion(vi, L"0.0.0.0"))
    {
        return EXIT_FAILURE;
    }

    std::srand(unsigned(std::time(0)));
    for (int i = 1; i < 10000; ++i)
    {
        vi.high = std::rand();
        vi.low = std::rand();
        vi.release = std::rand();
        vi.build = std::rand();
        if (!compareVersion(vi, std::to_wstring(vi.high) + L"." + std::to_wstring(vi.low) + L"." + std::to_wstring(vi.release) + L"." + std::to_wstring(vi.build)))
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}