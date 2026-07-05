#include "VehicleBusService.h"

#include <Arduino.h>
#include <driver/twai.h>
#include <esp_err.h>
#include <cstdio>

#include "../../logging/Logger.h"

namespace {

constexpr gpio_num_t kTwaiTxGpio = GPIO_NUM_21;
constexpr gpio_num_t kTwaiRxGpio = GPIO_NUM_22;
constexpr int kTwaiBitrate = 500000;
char logBuffer[128] = {};

void LogIntValue(const char* label, int value)
{
    std::snprintf(logBuffer, sizeof(logBuffer), "%s%d", label, value);
    Logger::Info(logBuffer);
}

void LogTwaiError(const char* action, esp_err_t error)
{
    std::snprintf(
        logBuffer,
        sizeof(logBuffer),
        "TWAI initialization failed during %s: %s",
        action,
        esp_err_to_name(error));
    Logger::Error(logBuffer);
}

} // namespace

void VehicleBusService::Initialize()
{
    Logger::Info("VehicleBusService initializing");
    LogIntValue("TWAI TX GPIO", static_cast<int>(kTwaiTxGpio));
    LogIntValue("TWAI RX GPIO", static_cast<int>(kTwaiRxGpio));
    LogIntValue("TWAI bitrate ", kTwaiBitrate);
    Logger::Warn("CANH/CANL not connected for this milestone");

    twai_general_config_t generalConfig = TWAI_GENERAL_CONFIG_DEFAULT(
        kTwaiTxGpio,
        kTwaiRxGpio,
        TWAI_MODE_NORMAL);
    twai_timing_config_t timingConfig = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t filterConfig = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    esp_err_t result = twai_driver_install(&generalConfig, &timingConfig, &filterConfig);
    if (result != ESP_OK && result != ESP_ERR_INVALID_STATE) {
        initialized = false;
        status = StatusCode::Error;
        lastError = StatusCode::HardwareUnavailable;
        LogTwaiError("driver install", result);
        return;
    }

    result = twai_start();
    if (result != ESP_OK && result != ESP_ERR_INVALID_STATE) {
        initialized = false;
        status = StatusCode::Error;
        lastError = StatusCode::HardwareUnavailable;
        LogTwaiError("driver start", result);
        return;
    }

    initialized = true;
    status = StatusCode::Ok;
    lastError = StatusCode::Ok;
    Logger::Info("TWAI initialized successfully");
}

void VehicleBusService::Update()
{
    // TWAI initialization only for this milestone. No frame receive or decoding.
}

const char* VehicleBusService::GetName() const
{
    return "vehicle_bus";
}

StatusCode VehicleBusService::GetStatus() const
{
    return status;
}

StatusCode VehicleBusService::GetLastError() const
{
    return lastError;
}

bool VehicleBusService::IsInitialized() const
{
    return initialized;
}
