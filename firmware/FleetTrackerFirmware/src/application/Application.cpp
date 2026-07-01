#include "Application.h"

#include <cstdio>

#include "../build/BuildInfo.h"
#include "../configuration/Configuration.h"
#include "../diagnostics/Diagnostics.h"
#include "../logging/Logger.h"
#include "../modules/ModuleManager.h"
#include "../platform/Platform.h"
#include "../platform/spi/SpiService.h"

namespace {

unsigned long lastHeartbeatMs = 0;
char bootLogBuffer[96] = {};

void LogBuildField(const char* label, const char* value)
{
    std::snprintf(bootLogBuffer, sizeof(bootLogBuffer), "%-16s: %s", label, value);
    Logger::Info(bootLogBuffer);
}

} // namespace

namespace Application {

void Initialize()
{
    Logger::Initialize();
    Logger::Info("GAS Smart Tracker booting...");
    Logger::Info("--------------------------------------------------");
    Logger::Info("GAS Smart Tracker");
    LogBuildField("Firmware Version", BuildInfo::GetFirmwareVersion());
    LogBuildField("Git Commit", BuildInfo::GetGitCommit());
    LogBuildField("Build Date", BuildInfo::GetBuildDate());
    LogBuildField("Build Time", BuildInfo::GetBuildTime());
    LogBuildField("Board", BuildInfo::GetBoardName());
    LogBuildField("Hardware", BuildInfo::GetHardwareName());
    LogBuildField("Build Type", BuildInfo::GetBuildType());
    Logger::Info("--------------------------------------------------");

    Platform::Initialize();
    Configuration::Load();

    Diagnostics::LogBootReport();

    Logger::Info("Platform initialized");
    Logger::Info("Configuration loaded");

    Logger::Info("Initializing SPI...");
    SpiService::Initialize();
    Logger::Info("SPI initialized");
    Logger::Info(SpiService::GetPinConfigurationSummary());

    ModuleManager::Initialize();
    Logger::Info("Module manager initialized");

    Diagnostics::Initialize();
    Logger::Info("Diagnostics initialized");

    Logger::Info("Application initialized");
}

void Update()
{
    const unsigned long nowMs = Platform::Millis();
    const unsigned long heartbeatIntervalMs = Configuration::Current().heartbeatIntervalMs;

    if ((nowMs - lastHeartbeatMs) >= heartbeatIntervalMs) {
        lastHeartbeatMs = nowMs;
        Logger::Info("GAS Smart Tracker heartbeat");
        Diagnostics::LogHeartbeat();
    }

    ModuleManager::Update();
    Platform::Delay(1);
}

} // namespace Application
