
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

std::wstring XmlParser::getPugiAttributeValue(const pugi::xml_node_iterator &nodeIter, const pugi::char_t *attributeName)
{
    auto pugiVal = nodeIter->attribute(attributeName).as_string();
#ifdef PUGIXML_WCHAR_MODE
    return pugiVal;
#else
    return pugi::as_wide(pugiVal);
    ;
#endif
}

bool XmlParser::getCurrentChannelType(const std::wstring &channelType)
{
    if (channelType.compare(L"") == 0)
        return false;

    auto xmlRootElement = m_xmlDoc.parent().begin();
    auto it = m_xmlDoc.begin();
    for (auto child = it->begin(); child != it->end(); ++child)
    {
        auto val = getPugiAttributeValue(child, "type");
        if (channelType.compare(val) == 0)
        {
            m_typeNodeIter = child;
            return true;
        }
    }
    return false;
}

bool XmlParser::getCurrentVersionInChannel()
{
    if (m_typeNodeIter->empty())
        return false;

    for (auto it = m_typeNodeIter->begin(); it != m_typeNodeIter->end(); ++it)
    {
        auto val = getPugiAttributeValue(it, "id");
        if (m_versionInfo.compare(VersionInfo(val)) == 0)
        {
            m_curVersionIter = it;
            return true;
        }
    }
    return false;
}

bool XmlParser::getNextVersionInChannel(bool isCritical)
{
    if (m_typeNodeIter->empty())
        return false;

    for (auto it = m_typeNodeIter->begin(); it != m_typeNodeIter->end(); ++it)
    {
        auto val = getPugiAttributeValue(it, "id");
        if (it->attribute("active").as_bool() &&
            m_versionInfo.compare(VersionInfo(val)) < 0)
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

bool XmlParser::getUpdateVersion(const std::wstring &channelType)
{
    if (!getCurrentChannelType(channelType))
        return false;

    // if (!getCurrentVersionInChannel())
    //     return false;

    // if (getNextVersionInChannel(true))
    //     return true;

    // if (getNextVersionInChannel(false))
    //     return true;

    return false;
}

void XmlParser::setCurrentVersion(const VersionInfo &val)
{
    m_versionInfo = val;
}
