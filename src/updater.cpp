
#include <stdio.h>
#include <wchar.h>
#include "updater.h"

const std::wstring Updater::getCurrentVersion() const
{
    return m_verInfo.toString();
}
