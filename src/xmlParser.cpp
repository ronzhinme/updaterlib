
#include <iostream>
#include "xmlParser.h"

XmlParser::XmlParser()
{
}

XmlParser::~XmlParser()
{
}

bool XmlParser::parseXmlFile(const std::string &filename)
{
    pugi::xml_parse_result result = m_xmlDoc.load_file(filename.c_str());
    return result.operator bool();
}

bool XmlParser::parseXmlData(const std::string &data, size_t dataLength)
{
    pugi::xml_parse_result result = m_xmlDoc.load_buffer(data.c_str(), dataLength);
    return result.operator bool();
}

std::string XmlParser::_getPugiAttributeValue(const pugi::xml_node_iterator &nodeIter,
                                             const pugi::char_t *attributeName)
{
    auto val = nodeIter->attribute(attributeName).as_string();
#ifdef PUGIXML_WCHAR_MODE
    return pugi::as_utf8(val);
#else
    return val;
#endif
}

std::string XmlParser::getNextVersionAttribute(const std::string &attribute)
{
    if (m_nextVersionIter->empty() || attribute.empty())
        return "";

    return _getPugiAttributeValue(m_nextVersionIter, attribute.c_str());
}

bool XmlParser::_getCurrentChannelType(const std::string &channelType)
{
    if (channelType.compare("") == 0 || m_xmlDoc.empty())
        return false;

    auto updateInfoNode = m_xmlDoc.first_child();
    for (auto it = updateInfoNode.begin(); it != updateInfoNode.end(); ++it)
    {
        auto val = _getPugiAttributeValue(it, "type");
        if (channelType.compare(val) == 0)
        {
            m_typeNodeIter = it;
            return true;
        }
    }
    return false;
}

bool XmlParser::_getCurrentVersionInChannel()
{
    if (m_typeNodeIter->empty())
        return false;

    for (auto it = m_typeNodeIter->begin(); it != m_typeNodeIter->end(); ++it)
    {
        auto val = _getPugiAttributeValue(it, "id");
        if (versionInfo.compare(VersionInfo(val)) == 0)
        {
            m_curVersionIter = it;
            return true;
        }
    }
    return false;
}

bool XmlParser::_getNextVersionInChannel(bool isCritical)
{
    if (m_typeNodeIter->empty())
        return false;

    for (auto it = m_typeNodeIter->begin(); it != m_typeNodeIter->end(); ++it)
    {
        auto val = _getPugiAttributeValue(it, "id");
        if (it->attribute("active").as_bool() &&
            versionInfo.compare(VersionInfo(val)) < 0)
        {
            m_nextVersionIter = it;
            if (it->attribute("critical").as_bool() && isCritical)
                return true;
        }
    }

    if (!isCritical && !m_nextVersionIter->empty())
        return true;

    return false;
}

bool XmlParser::getUpdateVersion(const std::string &channelType)
{
    if (!_getCurrentChannelType(channelType))
        return false;

    if (!_getCurrentVersionInChannel())
        return false;

    if (_getNextVersionInChannel(true))
        return true;

    if (_getNextVersionInChannel(false))
        return true;

    return false;
}
