
#include <cstdlib>
#include <ctime>
#include "../src/versionInfo.h"

bool compareVersion(const VersionInfo &vi, const std::wstring &val)
{
    if (vi.toString().compare(val) != 0)
    {
        wprintf(L"%ls %ls\n", vi.toString().c_str(), val.c_str());
        return false;
    }
    return true;
}

int main()
{
    // toString()
    VersionInfo vi;
    auto v = vi.toString();

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

    // fromString()
    VersionInfo vi1(L"1");              if(!compareVersion(vi1, L"1.0.0.0")) return EXIT_FAILURE;
    VersionInfo vi2(L"2.");             if(!compareVersion(vi2, L"2.0.0.0")) return EXIT_FAILURE;
    VersionInfo vi3(L"3.1");            if(!compareVersion(vi3, L"3.1.0.0")) return EXIT_FAILURE;
    VersionInfo vi4(L"4.2.");           if(!compareVersion(vi4, L"4.2.0.0")) return EXIT_FAILURE;
    VersionInfo vi5(L"5.3.1");          if(!compareVersion(vi5, L"5.3.1.0")) return EXIT_FAILURE;
    VersionInfo vi6(L"6.4.2.");         if(!compareVersion(vi6, L"6.4.2.0")) return EXIT_FAILURE;
    VersionInfo vi7(L"7.5.3.1");        if(!compareVersion(vi7, L"7.5.3.1")) return EXIT_FAILURE;
    VersionInfo vi8(L"8.6.4.2.");       if(!compareVersion(vi8, L"8.6.4.2")) return EXIT_FAILURE;

    VersionInfo vi9(L"...");            if(!compareVersion(vi9,  L"0.0.0.0")) return EXIT_FAILURE;
    VersionInfo vi10(L"....");          if(!compareVersion(vi10, L"0.0.0.0")) return EXIT_FAILURE;
    VersionInfo vi11(L" . . . .");      if(!compareVersion(vi11, L"0.0.0.0")) return EXIT_FAILURE;
    VersionInfo vi12(L" . . . . 1");    if(!compareVersion(vi12, L"1.0.0.0")) return EXIT_FAILURE;
    VersionInfo vi13(L"");              if(!compareVersion(vi13, L"0.0.0.0")) return EXIT_FAILURE;
    VersionInfo vi14(L"asaasasdas");    if(!compareVersion(vi14, L"0.0.0.0")) return EXIT_FAILURE;

    // less
    VersionInfo viLess0;
    VersionInfo viLess1(L"1.2.3.4");
    if(viLess0.less(VersionInfo())) return EXIT_FAILURE;
    if(!viLess0.less(VersionInfo(L"0.0.0.1"))) return EXIT_FAILURE;
    if(viLess1.less(VersionInfo(L"1.2.3.4"))) return EXIT_FAILURE;
    if(!viLess0.less(VersionInfo(L"0.0.0.1"))) return EXIT_FAILURE;
    if(!viLess1.less(VersionInfo(L"2.2.3.4"))) return EXIT_FAILURE;
    if(!viLess1.less(VersionInfo(L"1.3.3.4"))) return EXIT_FAILURE;
    if(!viLess1.less(VersionInfo(L"1.2.4.4"))) return EXIT_FAILURE;
    if(!viLess1.less(VersionInfo(L"1.2.3.5"))) return EXIT_FAILURE;
    if(viLess1.less(VersionInfo(L"1.2.3.3"))) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}