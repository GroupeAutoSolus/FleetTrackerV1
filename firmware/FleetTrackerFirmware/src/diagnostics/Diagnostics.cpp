#include "Diagnostics.h"

#include <cstdio>

#include "../configuration/Configuration.h"
#include "../logging/Logger.h"
#include "../modules/ModuleManager.h"
#include "../platform/Platform.h"

namespace {

constexpr const char* kBootStatusOk = "OK";
char logBuffer[96] = {};

void LogLabelValue(const char* label, const char* value)
{
    std::snprintf(logBuffer, sizeof(logBuffer), "%s: %s", label, value);
    Logger::Info(logBuffer);
}

void LogLabelValue(const char* label, unsigned long value)
{
    std::snprintf(logBuffer, sizeof(logBuffer), "%s: %lu", label, value);
    Logger::Info(logBuffer);
}

} // namespace

namespace Diagnostics {

void Initialize()
{
    // Reserved for future diagnostics state initialization.
}

const char* GetBootStatus()
{
    return kBootStatusOk;
}

void LogBootReport()
{
    LogLabelValue("Firmware version", Configuration::Current().firmwareVersion);
    LogLabelValue("Device ID", Configuration::Current().deviceId);
    LogLabelValue("Reset reason", Platform::ResetReason());
    LogLabelValue("Free heap bytes", Platform::FreeHeapBytes());
    LogLabelValue("Boot status", GetBootStatus());
}

void LogHeartbeat()
{
    LogLabelValue("Uptime ms", Platform::Millis());
    LogLabelValue("Free heap bytes", Platform::FreeHeapBytes());
    LogLabelValue("Module health", ModuleManager::GetStatusSummary());
}

} // namespace Diagnostics
