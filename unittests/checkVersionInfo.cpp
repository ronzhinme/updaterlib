
#include <cstdlib>
#include <ctime>
#include "../src/versionInfo.h"

int main()
{
    // toString()
    VersionInfo vi;
    auto && v = vi.toString();

    if (vi.compare(VersionInfo("0.0.0.0")) != 0)
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
        if (vi.compare(VersionInfo(std::to_string(vi.high) + "." + std::to_string(vi.low) + "." + std::to_string(vi.release) + "." + std::to_string(vi.build))) != 0)
        {
            return EXIT_FAILURE;
        }
    }

    VersionInfo vi1("1");
    if (vi1.compare(VersionInfo("1.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi2("2.");
    if (vi2.compare(VersionInfo("2.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi3("3.1");
    if (vi3.compare(VersionInfo("3.1.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi4("4.2.");
    if (vi4.compare(VersionInfo("4.2.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi5("5.3.1");
    if (vi5.compare(VersionInfo("5.3.1.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi6("6.4.2.");
    if (vi6.compare(VersionInfo("6.4.2.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi7("7.5.3.1");
    if (vi7.compare(VersionInfo("7.5.3.1")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi8("8.6.4.2.");
    if (vi8.compare(VersionInfo("8.6.4.2")) != 0)
        return EXIT_FAILURE;

    VersionInfo vi9("...");
    if (vi9.compare(VersionInfo("0.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi10("....");
    if (vi10.compare(VersionInfo("0.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi11(" . . . .");
    if (vi11.compare(VersionInfo("0.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi12(" . . . . 1");
    if (vi12.compare(VersionInfo("1.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi13("");
    if (vi13.compare(VersionInfo("0.0.0.0")) != 0)
        return EXIT_FAILURE;
    VersionInfo vi14("asaasasdas");
    if (vi14.compare(VersionInfo("0.0.0.0")) != 0)
        return EXIT_FAILURE;

    VersionInfo viLess0;
    VersionInfo viLess1("1.2.3.4");
    if (viLess0.compare(VersionInfo()) != 0)
        return EXIT_FAILURE;
    if (viLess0.compare(VersionInfo("0.0.0.1")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo("1.2.3.4")) != 0)
        return EXIT_FAILURE;
    if (viLess0.compare(VersionInfo("0.0.0.1")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo("2.2.3.4")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo("1.3.3.4")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo("1.2.4.4")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo("1.2.3.5")) >= 0)
        return EXIT_FAILURE;
    if (viLess1.compare(VersionInfo("1.2.3.3")) <= 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}