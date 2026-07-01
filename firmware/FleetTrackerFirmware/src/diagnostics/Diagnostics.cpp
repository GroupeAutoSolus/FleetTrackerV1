#include "Diagnostics.h"

#include <cstdio>

#include "../configuration/Configuration.h"
#include "../logging/Logger.h"
#include "../modules/ModuleManager.h"
#include "../platform/Platform.h"

namespace {

constexpr const char* kBootStatusOk = "OK";
constexpr unsigned long kVolatileBootCounterPlaceholder = 1;
char logBuffer[160] = {};

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

void LogKeyValue(const char* key, const char* value)
{
    std::snprintf(logBuffer, sizeof(logBuffer), "  %s=%s", key, value);
    Logger::Info(logBuffer);
}

void LogKeyValue(const char* key, unsigned long value)
{
    std::snprintf(logBuffer, sizeof(logBuffer), "  %s=%lu", key, value);
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
    Logger::Info("Boot diagnostics:");
    LogLabelValue("Firmware version", Configuration::Current().firmwareVersion);
    LogLabelValue("Device ID", Configuration::Current().deviceId);
    LogLabelValue("Reset reason", Platform::ResetReason());
    LogLabelValue("Free heap bytes", Platform::FreeHeapBytes());
    LogLabelValue("Boot count placeholder", kVolatileBootCounterPlaceholder);
    LogLabelValue("Boot status", GetBootStatus());
}

void LogHeartbeat()
{
    Logger::Info("Heartbeat diagnostics:");
    LogKeyValue("uptime_ms", Platform::Millis());
    LogKeyValue("free_heap_bytes", Platform::FreeHeapBytes());
    LogKeyValue("module_health", ModuleManager::GetStatusSummary());
}

} // namespace Diagnostics
