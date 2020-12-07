
#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <functional>
#include <openssl/sha.h>
#include <memory>
#include <thread>

#include "updater.h"
#include "platformSpecific.h"

using namespace std::placeholders;

void _onResultEvent(Updater *updater, OperationType o, Result r, const ExtraInfo &i)
{
    if(updater->operationResult()!=nullptr)
    {
        updater->operationResult()(o, r, i);
    }

    if (!updater->isCheckAndUpdate())
    {
        return;
    }

    if (o == TYPE_DOWNLOAD_INFO && r == RESULT_SUCCESS)
    {
        updater->findUpdateVersion();
    }

    if (o == TYPE_CHECK_UPDATE_VERSION && r == RESULT_SUCCESS)
    {
        updater->downloadUpdate();
    }

    if (o == TYPE_DOWNLOAD_UPDATE && r == RESULT_SUCCESS)
    {
        updater->checkUpdateSignature();
    }

    if (o == TYPE_CHECK_SIGNATURE && r == RESULT_SUCCESS)
    {
        updater->runInstaller();
    }

    if (o == TYPE_RUN_INSTALLER && r == RESULT_SUCCESS)
    {
        updater->stopOperation();
    }
}

ExtraInfo::ExtraInfo(const void *val, size_t len) : info(NULL), infoLength(0)
{
    if (val == NULL)
        return;

    infoLength = len;
    info = new char[infoLength];
    memcpy(info, val, infoLength);
}

ExtraInfo::~ExtraInfo()
{
    if (info != NULL)
    {
        delete[] info;
        info = NULL;
    }
}

Updater::Updater()
    : m_xmlData(""), m_autoUpdateInterval(0), m_channel(""), m_infoUrl(""), m_currentState(STATE_READY), m_isCheckAndUpdate(false)
{
    m_xmlParser.reset(new XmlParser());
    m_curlBridge.reset(new CurlBridge());
}

Updater::Updater(const Updater &src)
{
    _copyData(src);
}

Updater Updater::operator=(const Updater &src)
{
    Updater res;
    res._copyData(src);
    return res;
}

void Updater::setVersionInfoUrl(const std::string &url)
{
    m_infoUrl = url;
}

const std::string &Updater::getChannel() const
{
    return m_channel;
}

void Updater::setChannel(const std::string &channel)
{
    m_channel = channel;
}

const std::string &Updater::getVersionInfoUrl() const
{
    return m_infoUrl;
}

unsigned long Updater::getAutoUpdateInterval() const
{
    return m_autoUpdateInterval;
}

void Updater::setAutoUpdateInterval(unsigned long hours)
{
    m_autoUpdateInterval = hours;
}

void Updater::_appendDataToTempUpdateFile(const void *data, size_t dataSize)
{
    fwrite(data, dataSize, 1, updateFile);
    auto fileSize = ftell(updateFile);

    m_downloadProgress.current = fileSize;
    _onResultEvent(this, TYPE_DOWNLOAD_UPDATE, RESULT_INPROGRESS, ExtraInfo(&m_downloadProgress, sizeof(DownloadBytesInfo)));
}

void Updater::_onDataReceived(OperationType operationType, const char *data, size_t dataSize)
{
    switch (operationType)
    {
    case TYPE_DOWNLOAD_INFO:
        m_xmlData.append(data);
        break;
    case TYPE_DOWNLOAD_UPDATE:
        _appendDataToTempUpdateFile(data, dataSize);
        break;
    }
}

void Updater::downloadInfo()
{
    m_currentState = STATE_CHECKING;
    if (m_operationResult != NULL)
    {
        _onResultEvent(this, TYPE_DOWNLOAD_INFO, RESULT_INPROGRESS, ExtraInfo(m_infoUrl.c_str(), m_infoUrl.length()));
    }

    m_xmlData.clear();
    m_curlBridge->onDataReceivedEvent([this](const char *d, size_t l) mutable { this->_onDataReceived(TYPE_DOWNLOAD_INFO, d, l); });
    m_curlBridge->onDataReceivedFinished([this]() {
        if (m_operationResult != NULL)
        {
            _onResultEvent(this, TYPE_DOWNLOAD_INFO, RESULT_SUCCESS, ExtraInfo());
        }
    });
    m_curlBridge->getUrlData(m_infoUrl);

    return;
}

void Updater::findUpdateVersion()
{
    if (m_operationResult != NULL)
    {
        _onResultEvent(this, TYPE_CHECK_UPDATE_VERSION, RESULT_INPROGRESS, ExtraInfo());
    }

    auto res = m_xmlParser->parseXmlData(m_xmlData, m_xmlData.length());
    if (!res && m_operationResult != NULL)
    {
        _onResultEvent(this, TYPE_CHECK_UPDATE_VERSION, RESULT_FAILED, ExtraInfo("parseXmlData", 13));
    }

    m_xmlParser->versionInfo = versionInfo;
    res = m_xmlParser->getUpdateVersion(m_channel);
    if (m_operationResult != NULL)
    {
        if (res)
            _onResultEvent(this, TYPE_CHECK_UPDATE_VERSION, RESULT_SUCCESS, ExtraInfo());
        else
            _onResultEvent(this, TYPE_CHECK_UPDATE_VERSION, RESULT_FAILED, ExtraInfo());
    }
}

std::string Updater::getNextVersionAttribute(const std::string &attribute)
{
    return m_xmlParser->getNextVersionAttribute(attribute);
}

void Updater::downloadUpdate()
{
    m_currentState = STATE_DOWNLOADING;
    remove(UPDATE_FILENAME.c_str());
    updateFile = fopen(UPDATE_FILENAME.c_str(), "ab");

    auto installerUrl = getNextVersionAttribute("url");
    auto updateSize = getNextVersionAttribute("size");
    m_downloadProgress.total = std::stoull(updateSize);

    if (m_operationResult != NULL)
    {
        _onResultEvent(this, TYPE_DOWNLOAD_UPDATE, RESULT_INPROGRESS, ExtraInfo(installerUrl.c_str(), installerUrl.length()));
    }

    m_curlBridge->onDataReceivedEvent([this, updateSize](const char *d, size_t l) mutable {
        this->_onDataReceived(TYPE_DOWNLOAD_UPDATE, d, l);
    });

    m_curlBridge->onDataReceivedFinished([this]() {
        if (m_operationResult != NULL)
        {
            fclose(updateFile);
            _onResultEvent(this, TYPE_DOWNLOAD_UPDATE, RESULT_SUCCESS, ExtraInfo());
        }
    });
    m_curlBridge->getUrlData(installerUrl);

    return;
}

void Updater::checkUpdateSignature()
{
    if (m_operationResult != NULL)
    {
        _onResultEvent(this, TYPE_CHECK_SIGNATURE, RESULT_INPROGRESS, ExtraInfo());
    }

    auto signatureStr = getNextVersionAttribute("signature");
    if (signatureStr.length() != SHA512_DIGEST_LENGTH * 2)
    {
        _onResultEvent(this, TYPE_CHECK_SIGNATURE, RESULT_FAILED, ExtraInfo());
    }

    printf("signature\n");
    unsigned char signature[SHA512_DIGEST_LENGTH];
    for (auto i = 0; i < SHA512_DIGEST_LENGTH; ++i)
    {
        signature[i] = std::stoi(signatureStr.substr(i << 1, 2), 0, 16);
    }

    unsigned char sha512Signature[SHA512_DIGEST_LENGTH];
    if (m_operationResult != NULL && !_getSHA512FromUpdate(sha512Signature))
    {
        _onResultEvent(this, TYPE_CHECK_SIGNATURE, RESULT_FAILED, ExtraInfo());
    }

    auto result = memcmp(signature, sha512Signature, SHA512_DIGEST_LENGTH);

    if (m_operationResult != NULL)
    {
        if (result != 0)
            _onResultEvent(this, TYPE_CHECK_SIGNATURE, RESULT_FAILED, ExtraInfo());
        else
            _onResultEvent(this, TYPE_CHECK_SIGNATURE, RESULT_SUCCESS, ExtraInfo());
    }

    return;
}

bool Updater::_getSHA512FromUpdate(unsigned char *sha512Signature)
{
    SHA512_CTX context;
    if (!SHA512_Init(&context))
    {
        return false;
    }

    auto file = fopen(UPDATE_FILENAME.c_str(), "rb");
    unsigned char ch;
    while (fread(&ch, sizeof(unsigned char), 1, file) > 0)
    {
        if (!SHA512_Update(&context, &ch, sizeof(unsigned char)))
        {
            return false;
        }
    }

    if (!SHA512_Final(sha512Signature, &context))
    {
        return false;
    }

    return true;
}

void Updater::runInstaller()
{
    m_currentState = STATE_UPDATING;
    if (m_operationResult != NULL)
    {
        _onResultEvent(this, TYPE_RUN_INSTALLER, RESULT_INPROGRESS, ExtraInfo());
    }

    auto argStr = getNextVersionAttribute("updateargs");
    PlatformSpecific::runInstaller(UPDATE_FILENAME, argStr);
    if (m_operationResult != NULL)
    {
        _onResultEvent(this, TYPE_RUN_INSTALLER, RESULT_SUCCESS, ExtraInfo());
    }

    return;
}

void Updater::onOperationResultEvent(OperationResultFunction handler)
{
    m_operationResult = handler;
}

OperationResultFunction Updater::operationResult() const
{
    return m_operationResult;
}

void Updater::_copyData(const Updater &src)
{
    m_infoUrl = src.m_infoUrl;
    m_channel = src.m_channel;
    m_autoUpdateInterval = src.m_autoUpdateInterval;
    m_xmlData = src.m_xmlData;
    m_operationResult = src.m_operationResult;
    m_curlBridge = src.m_curlBridge;
    m_xmlParser = src.m_xmlParser;
    m_currentState = src.m_currentState;
    m_isCheckAndUpdate = src.m_isCheckAndUpdate;
}

UpdaterState Updater::getCurrentState()
{
    return m_currentState;
}

void _checkAndUpdateThread(Updater *updater)
{
    updater->downloadInfo();
    while (updater->getCurrentState() != STATE_READY)
    {
        std::this_thread::yield();
    }
}

void Updater::checkAndUpdate()
{
    if (m_currentState != STATE_READY)
    {
        return;
    }

    m_isCheckAndUpdate = true;
    std::thread checkThread(_checkAndUpdateThread, this);
    checkThread.join();
}

void Updater::stopOperation()
{
    m_currentState = STATE_READY;
    m_isCheckAndUpdate = false;
}

bool Updater::isCheckAndUpdate()
{
    return m_isCheckAndUpdate;
}

void Updater::pauseDownloading()
{
    m_curlBridge->pauseDownloading();
    m_currentState = STATE_PAUSED;
}

void Updater::resumeDownloading()
{
    m_curlBridge->resumeDownloading();
    m_currentState = STATE_DOWNLOADING;
}