#include "Application.h"

#include "../configuration/Configuration.h"
#include "../logging/Logger.h"
#include "../platform/Platform.h"

namespace {

unsigned long lastHeartbeatMs = 0;

} // namespace

namespace Application {

void Initialize()
{
    Logger::Initialize();
    Logger::Info("GAS Smart Tracker booting...");

    Logger::Info("Firmware version:");
    Logger::Info(Configuration::Current().firmwareVersion);

    Platform::Initialize();
    Logger::Info("Platform initialized");

    Configuration::Load();
    Logger::Info("Configuration loaded");

    Logger::Info("Application initialized");
}

void Update()
{
    const unsigned long nowMs = Platform::Millis();
    const unsigned long heartbeatIntervalMs = Configuration::Current().heartbeatIntervalMs;

    if ((nowMs - lastHeartbeatMs) >= heartbeatIntervalMs) {
        lastHeartbeatMs = nowMs;
        Logger::Info("GAS Smart Tracker heartbeat");
    }

    Platform::Delay(1);
}

} // namespace Application
