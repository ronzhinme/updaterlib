
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

    xmlParser.versionInfo = VersionInfo("0.0.0.1");
    bool stableResult = xmlParser.getUpdateVersion("stable");
    if(!stableResult)
    {
        printf(R"(getUpdateVersion("stable")\n)");
        return EXIT_FAILURE;
    }
    
    bool alphaResult = xmlParser.getUpdateVersion("alpha");
    if(!alphaResult)
    {
        printf(R"(getUpdateVersion("alpha")\n)");
        return EXIT_FAILURE;
    }

    bool betaResult = xmlParser.getUpdateVersion("beta");
    if(betaResult)
    {
        printf(R"(getUpdateVersion("beta")\n)");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}