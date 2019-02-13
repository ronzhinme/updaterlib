

#include "../src/updater.h"

int main()
{
    VersionInfo vi;
    auto v = vi.ToString();

    if (vi.ToString().compare(L"0.0.0.0") != 0)
    {
        return EXIT_FAILURE;
    }

    for (int i = 1; i < 10000; ++i)
    {
        vi.major = i;
        if (vi.ToString().compare(std::to_wstring(i) + L".0.0.0") != 0)
        {
            wprintf(L"%ls \n", vi.ToString().c_str());
            return EXIT_FAILURE;
        }

        vi.minor = i;
        if (vi.ToString().compare(std::to_wstring(vi.major) + L"." +
                                  std::to_wstring(i) + L".0.0") != 0)
        {
            wprintf(L"%ls \n", vi.ToString().c_str());
            return EXIT_FAILURE;
        }

        vi.release = i;
        if (vi.ToString().compare(std::to_wstring(vi.major) + L"." +
                                  std::to_wstring(vi.minor) + L"." +
                                  std::to_wstring(i) + L".0") != 0)
        {
            wprintf(L"%ls \n", vi.ToString().c_str());
            return EXIT_FAILURE;
        }

        vi.build = i;
        if (vi.ToString().compare(std::to_wstring(vi.major) + L"." +
                                  std::to_wstring(vi.minor) + L"." +
                                  std::to_wstring(vi.release) + L"." +
                                  std::to_wstring(i)) != 0)
        {
            wprintf(L"%ls \n", vi.ToString().c_str());
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}