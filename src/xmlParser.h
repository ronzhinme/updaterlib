
#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>

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
    xmlDocPtr m_xmlDoc;
};

#endif