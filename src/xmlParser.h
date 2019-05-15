
#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <pugixml.hpp>
#include "versionInfo.h"

class XmlParser
{
public:
    XmlParser();
    ~XmlParser();

    void setCurrentVersion(const VersionInfo& val);
    bool getUpdateVersion(const std::wstring & channelType = std::wstring());
    bool parseXmlFile(const std::string & filename);
    bool parseXmlData(const std::string & data, size_t dataLength);
private:
    bool getNextVersionInChannel(bool isCritical);
    bool getCurrentChannelType(const std::wstring & channelType);
    bool getCurrentVersionInChannel();
    pugi::xml_document m_xmlDoc;
    VersionInfo m_versionInfo;
    pugi::xml_node_iterator m_typeNodeIter;
    pugi::xml_node_iterator m_curVersionIter;
    pugi::xml_node_iterator m_nextVersionIter;
    std::wstring getPugiAttributeValue(const pugi::xml_node_iterator & nodeIter, const pugi::char_t * attributeName);
};

#endif