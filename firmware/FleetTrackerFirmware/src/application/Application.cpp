#include "Application.h"

#include "../configuration/Configuration.h"
#include "../diagnostics/Diagnostics.h"
#include "../logging/Logger.h"
#include "../modules/ModuleManager.h"
#include "../platform/Platform.h"
#include "../platform/spi/SpiService.h"

namespace {

unsigned long lastHeartbeatMs = 0;

} // namespace

namespace Application {

void Initialize()
{
    Logger::Initialize();
    Logger::Info("GAS Smart Tracker booting...");

    Platform::Initialize();
    Configuration::Load();

    Diagnostics::LogBootReport();

    Logger::Info("Platform initialized");
    Logger::Info("Configuration loaded");

    SpiService::Initialize();
    Logger::Info("SPI service initialized");
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
