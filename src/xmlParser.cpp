
#include "xmlParser.h"

XmlParser::XmlParser()
    : m_xmlDoc(NULL)
{
}

XmlParser::~XmlParser()
{
    xmlFreeDoc(m_xmlDoc);
    xmlCleanupParser();
}

void XmlParser::parseXmlFile(const std::string &filename)
{
    m_xmlDoc = xmlReadFile(filename.c_str(), NULL, 0);
}

void XmlParser::parseXmlData(const std::string &data, size_t dataLength)
{
    m_xmlDoc = xmlReadMemory(data.c_str(), dataLength, "", NULL, 0);
}

void XmlParser::getLatestVersion() const
{
    if (m_xmlDoc == nullptr)
        return;

    auto xmlRootElement = xmlDocGetRootElement(m_xmlDoc);
    for (auto item = xmlRootElement; item; item = item->next)
    {
        if (item->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", item->name);
        }
    }
}

void XmlParser::setCurrentVersion()
{
}

void XmlParser::getNextCriticalUpdate() const
{
}