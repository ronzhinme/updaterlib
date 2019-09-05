
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
    XmlParser(const XmlParser & src) = delete;
    XmlParser operator=(const XmlParser & src) = delete;

    VersionInfo versionInfo;
    bool getUpdateVersion(const std::string &channelType = std::string());
    bool parseXmlFile(const std::string &filename);
    bool parseXmlData(const std::string &data, size_t dataLength);
    std::string getNextVersionAttribute(const std::string &attribute);

private:
    bool _getNextVersionInChannel(bool isCritical);
    bool _getCurrentChannelType(const std::string &channelType);
    bool _getCurrentVersionInChannel();
    pugi::xml_document m_xmlDoc;
    pugi::xml_node_iterator m_typeNodeIter;
    pugi::xml_node_iterator m_curVersionIter;
    pugi::xml_node_iterator m_nextVersionIter;
    std::string _getPugiAttributeValue(const pugi::xml_node_iterator &nodeIter, const pugi::char_t *attributeName);
};

#endif