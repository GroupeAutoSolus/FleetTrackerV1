#include "TwaiCanInterface.h"

#include <Arduino.h>
#include <driver/twai.h>
#include <cstdio>

#include "../../configuration/Configuration.h"
#include "../../logging/Logger.h"

namespace {

constexpr gpio_num_t kTwaiTxGpio = GPIO_NUM_21;
constexpr gpio_num_t kTwaiRxGpio = GPIO_NUM_22;
char logBuffer[160] = {};

void LogPin(const char* label, gpio_num_t pin)
{
    std::snprintf(logBuffer, sizeof(logBuffer), "%s=%d", label, static_cast<int>(pin));
    Logger::Info(logBuffer);
}

void LogFrame(const twai_message_t& message)
{
    const int idWidth = (message.flags & TWAI_MSG_FLAG_EXTD) ? 8 : 3;
    int written = std::snprintf(
        logBuffer,
        sizeof(logBuffer),
        "CAN ID=0x%0*lX DLC=%u DATA=",
        idWidth,
        static_cast<unsigned long>(message.identifier),
        static_cast<unsigned int>(message.data_length_code));

    for (uint8_t i = 0; i < message.data_length_code && i < TWAI_FRAME_MAX_DLC && written > 0 && written < static_cast<int>(sizeof(logBuffer)); ++i) {
        written += std::snprintf(
            logBuffer + written,
            sizeof(logBuffer) - static_cast<size_t>(written),
            "%s%02X",
            i == 0 ? "" : " ",
            message.data[i]);
    }

    Logger::Info(logBuffer);
}

} // namespace

void TwaiCanInterface::Initialize()
{
    Logger::Info("Initializing TWAI CAN interface...");
    LogPin("TWAI TX GPIO", kTwaiTxGpio);
    LogPin("TWAI RX GPIO", kTwaiRxGpio);
    Logger::Info("TWAI receive scaffold enabled");
    Logger::Warn("CANH/CANL must remain disconnected until vehicle test milestone");

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
    if (!initialized) {
        return;
    }

    twai_message_t message = {};
    const esp_err_t result = twai_receive(&message, 0);
    if (result == ESP_OK && Configuration::Current().rawCanLoggingEnabled) {
        LogFrame(message);
    }
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
