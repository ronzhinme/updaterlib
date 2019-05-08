
#include "xmlParser.h"

XmlParser::XmlParser()
{
}

XmlParser::~XmlParser()
{
}

void XmlParser::parseXmlFile(const std::string &filename)
{
    pugi::xml_parse_result result = m_xmlDoc.load_file(filename.c_str());
}

void XmlParser::parseXmlData(const std::string &data, size_t dataLength)
{
    pugi::xml_parse_result result = m_xmlDoc.load_buffer(data.c_str(), dataLength);
}

void XmlParser::getLatestVersion() const
{
    
    auto xmlRootElement = m_xmlDoc.parent();
    for (auto it = m_xmlDoc.begin(); it != m_xmlDoc.end(); ++it)
    {
            printf("name: %ls\n", (wchar_t*)it->name());
    }
}

void XmlParser::setCurrentVersion()
{
}

void XmlParser::getNextCriticalUpdate() const
{
}