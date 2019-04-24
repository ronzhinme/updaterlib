
#include "../src/curlBridge.h"

#if defined(WIN32)
#include <windows.h>
#endif

int main()
{
    const std::string fData = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<note>\r\n\
  <to>Tove</to>\r\n\
  <from>Jani</from>\r\n\
  <heading>Reminder</heading>\r\n\
  <body>Don't forget me this weekend!</body>\r\n\
</note>";
    
    CurlBridge curlBridge;
    const std::string url("https://www.w3schools.com/xml/note.xml");
    std::string urlData;
    curlBridge.onDataReceivedEvent([&urlData](const char *d, size_t l) { urlData.append(d);});
    
    bool result = false; 
    curlBridge.onDataReceivedFinished([&result, &fData, &urlData]() mutable {
        result = fData.compare(urlData.c_str())==0;
    });
    
    if(!curlBridge.getUrlData(url))
    {
        fprintf(stderr, "getUrlData() error!");
        return EXIT_FAILURE;
    }

    return result ? EXIT_SUCCESS : EXIT_FAILURE;
}