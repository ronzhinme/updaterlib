
#include "../src/curlBridge.h"

#if defined(WIN32)
#include <windows.h>
#endif

#include <iostream>

int main()
{
    const std::string fData = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<note>\n\
  <to>Tove</to>\n\
  <from>Jani</from>\n\
  <heading>Reminder</heading>\n\
  <body>Don't forget me this weekend!</body>\n\
</note>";
    
    CurlBridge curlBridge;
    const std::string url("https://www.w3schools.com/xml/note.xml");
    std::string urlData;
    curlBridge.onDataReceivedEvent([&urlData](const char *d, size_t l) { urlData.append(d);});
    
    bool result = false; 
    curlBridge.onDataReceivedFinished([&result, &fData, &urlData]() mutable {

        std::cout << urlData.c_str() << std::endl << fData.c_str() << std::endl << fData.compare(urlData.c_str()) <<std::endl;
        result = fData.compare(urlData.c_str())==0;
    });
    
    if(!curlBridge.getUrlData(url))
    {
        fprintf(stderr, "getUrlData() error!");
        return EXIT_FAILURE;
    }

    return result ? EXIT_SUCCESS : EXIT_FAILURE;
}