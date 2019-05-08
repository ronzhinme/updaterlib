
#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <pugixml.hpp>

class XmlParser
{
public:
    XmlParser();
    ~XmlParser();

    void setCurrentVersion();
    void getLatestVersion() const;
    void parseXmlFile(const std::string & filename);
    void parseXmlData(const std::string & data, size_t dataLength);
private:
    void getNextCriticalUpdate() const;
    pugi::xml_document m_xmlDoc;
};

#endif