
#include <cstdlib>
#include <ctime>
#include "../src/versionInfo.h"

int main()
{
    // toString()
    VersionInfo vi;
    auto v = vi.toString();

    if (vi.compare(VersionInfo(L"0.0.0.0")) != 0)
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
        if (vi.compare(VersionInfo(std::to_wstring(vi.high) + L"." + std::to_wstring(vi.low) + L"." + std::to_wstring(vi.release) + L"." + std::to_wstring(vi.build))) != 0)
        {
            return EXIT_FAILURE;
        }
    }

    VersionInfo vi1(L"1");
    if (vi1.compare(VersionInfo(L"1.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi2(L"2.");
    if (vi2.compare(VersionInfo(L"2.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi3(L"3.1");
    if (vi3.compare(VersionInfo(L"3.1.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi4(L"4.2.");
    if (vi4.compare(VersionInfo(L"4.2.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi5(L"5.3.1");
    if (vi5.compare(VersionInfo(L"5.3.1.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi6(L"6.4.2.");
    if (vi6.compare(VersionInfo(L"6.4.2.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi7(L"7.5.3.1");
    if (vi7.compare(VersionInfo(L"7.5.3.1")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi8(L"8.6.4.2.");
    if (vi8.compare(VersionInfo(L"8.6.4.2")) != 0)
        return EXIT_FAILURE;

    VersionInfo vi9(L"...");
    if (vi9.compare(VersionInfo(L"0.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi10(L"....");
    if (vi10.compare(VersionInfo(L"0.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi11(L" . . . .");
    if (vi11.compare(VersionInfo(L"0.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi12(L" . . . . 1");
    if (vi12.compare(VersionInfo(L"1.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi13(L"");
    if (vi13.compare(VersionInfo(L"0.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi14(L"asaasasdas");
    if (vi14.compare(VersionInfo(L"0.0.0.0")) != 0)
        return EXIT_FAILURE;

    VersionInfo viLess0;
    VersionInfo viLess1(L"1.2.3.4");
    if (viLess0.compare(VersionInfo()) != 0)
        return EXIT_FAILURE;
    if (viLess0.compare(VersionInfo(L"0.0.0.1")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo(L"1.2.3.4")) != 0)
        return EXIT_FAILURE;
    if (viLess0.compare(VersionInfo(L"0.0.0.1")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo(L"2.2.3.4")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo(L"1.3.3.4")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo(L"1.2.4.4")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo(L"1.2.3.5")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo(L"1.2.3.3")) <= 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}