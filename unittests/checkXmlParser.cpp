
#include <stdlib.h>
#include "../src/xmlParser.h"

int main()
{
    XmlParser xmlParser;
    bool result = xmlParser.parseXmlFile("../../unittests/appUpdateSample.xml");
    xmlParser.setCurrentVersion(VersionInfo(L"0.0.0.1"));
    auto stableResult = xmlParser.getLatestVersion(L"stable");
    auto alphaResult = xmlParser.getLatestVersion(L"alpha");
    auto betaResult = xmlParser.getLatestVersion(L"beta");

    return result && stableResult && alphaResult && !betaResult ? EXIT_SUCCESS : EXIT_FAILURE;
}