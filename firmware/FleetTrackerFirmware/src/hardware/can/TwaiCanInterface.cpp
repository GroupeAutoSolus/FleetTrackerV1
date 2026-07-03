#include "TwaiCanInterface.h"

#include <Arduino.h>
#include <driver/twai.h>
#include <cstdio>

#include "../../logging/Logger.h"

namespace {

constexpr gpio_num_t kTwaiTxGpio = GPIO_NUM_21;
constexpr gpio_num_t kTwaiRxGpio = GPIO_NUM_22;
char logBuffer[64] = {};

void LogPin(const char* label, gpio_num_t pin)
{
    std::snprintf(logBuffer, sizeof(logBuffer), "%s=%d", label, static_cast<int>(pin));
    Logger::Info(logBuffer);
}

} // namespace

void TwaiCanInterface::Initialize()
{
    Logger::Info("Initializing TWAI CAN interface...");
    LogPin("TWAI TX GPIO", kTwaiTxGpio);
    LogPin("TWAI RX GPIO", kTwaiRxGpio);

    twai_general_config_t generalConfig = TWAI_GENERAL_CONFIG_DEFAULT(
        kTwaiTxGpio,
        kTwaiRxGpio,
        TWAI_MODE_NORMAL);
    twai_timing_config_t timingConfig = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t filterConfig = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    esp_err_t result = twai_driver_install(&generalConfig, &timingConfig, &filterConfig);
    if (result == ESP_ERR_INVALID_STATE) {
        result = ESP_OK;
    }

    if (result == ESP_OK) {
        result = twai_start();
        if (result == ESP_ERR_INVALID_STATE) {
            result = ESP_OK;
        }
    }

    if (result == ESP_OK) {
        initialized = true;
        status = StatusCode::Ok;
        lastError = StatusCode::Ok;
        Logger::Info("TWAI initialized successfully");
        return;
    }

    initialized = false;
    status = StatusCode::Error;
    lastError = StatusCode::HardwareUnavailable;
    Logger::Error("TWAI initialization failed");
}

void TwaiCanInterface::Update()
{
    // No CAN frame reading in this milestone.
}

const char* TwaiCanInterface::GetName() const
{
    return "vehicle_can_twai";
}

StatusCode TwaiCanInterface::GetStatus() const
{
    return status;
}

StatusCode TwaiCanInterface::GetLastError() const
{
    return lastError;
}

bool TwaiCanInterface::IsInitialized() const
{
    return initialized;
}
