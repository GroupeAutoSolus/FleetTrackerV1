#include "BuildInfo.h"

namespace BuildInfo {

const char* GetFirmwareVersion()
{
    return "0.10.0-dev";
}

const char* GetGitCommit()
{
    return "placeholder";
}

const char* GetBuildDate()
{
    return __DATE__;
}

const char* GetBuildTime()
{
    return __TIME__;
}

const char* GetBoardName()
{
    return "ESP32 DevKit V1";
}

const char* GetHardwareName()
{
    return "ESP32-WROOM-32";
}

const char* GetBuildType()
{
    return "Development";
}

} // namespace BuildInfo
