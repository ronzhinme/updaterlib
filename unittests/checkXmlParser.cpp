
#include <stdlib.h>
#include "../src/xmlParser.h"

int main()
{
    XmlParser xmlParser;
    bool result = xmlParser.parseXmlFile("../../unittests/appUpdateSample.xml");
    xmlParser.setCurrentVersion(VersionInfo(L"0.0.0.1"));
    auto stableResult = xmlParser.getUpdateVersion(L"stable");
    auto alphaResult = xmlParser.getUpdateVersion(L"alpha");
    auto betaResult = xmlParser.getUpdateVersion(L"beta");

    return result && stableResult && alphaResult && !betaResult ? EXIT_SUCCESS : EXIT_FAILURE;
}