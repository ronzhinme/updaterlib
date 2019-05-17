
#include <stdlib.h>
#include "../src/xmlParser.h"

int main()
{
    XmlParser xmlParser;
    bool result = xmlParser.parseXmlFile("appUpdateSample.xml");
    if(!result)
    {
        printf("xmlParser.parseXmlFile\n");
        return EXIT_FAILURE;
    }

    xmlParser.setCurrentVersion(VersionInfo(L"0.0.0.1"));
    bool stableResult = xmlParser.getUpdateVersion(L"stable");
    if(!stableResult)
    {
        printf(R"(getUpdateVersion(L"stable")\n)");
        return EXIT_FAILURE;
    }
    
    bool alphaResult = xmlParser.getUpdateVersion(L"alpha");
    if(!alphaResult)
    {
        printf(R"(getUpdateVersion(L"alpha")\n)");
        return EXIT_FAILURE;
    }

    bool betaResult = xmlParser.getUpdateVersion(L"beta");
    if(betaResult)
    {
        printf(R"(getUpdateVersion(L"beta")\n)");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}