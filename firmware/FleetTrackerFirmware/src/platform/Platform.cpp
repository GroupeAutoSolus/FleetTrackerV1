#include "Platform.h"

#include <Arduino.h>
#include <esp_system.h>

namespace {

const char* ResetReasonToString(esp_reset_reason_t reason)
{
    switch (reason) {
    case ESP_RST_POWERON:
        return "POWERON_RESET";
    case ESP_RST_EXT:
        return "EXTERNAL_RESET";
    case ESP_RST_SW:
        return "SOFTWARE_RESET";
    case ESP_RST_PANIC:
        return "PANIC_RESET";
    case ESP_RST_INT_WDT:
        return "INTERRUPT_WATCHDOG_RESET";
    case ESP_RST_TASK_WDT:
        return "TASK_WATCHDOG_RESET";
    case ESP_RST_WDT:
        return "WATCHDOG_RESET";
    case ESP_RST_DEEPSLEEP:
        return "DEEP_SLEEP_RESET";
    case ESP_RST_BROWNOUT:
        return "BROWNOUT_RESET";
    case ESP_RST_SDIO:
        return "SDIO_RESET";
    case ESP_RST_UNKNOWN:
    default:
        return "UNKNOWN_RESET";
    }
}

} // namespace

namespace Platform {

void Initialize()
{
    // Reserved for future platform-level ESP32 initialization.
}

unsigned long Millis()
{
    return millis();
}

void Delay(unsigned long milliseconds)
{
    delay(milliseconds);
}

unsigned long FreeHeapBytes()
{
    return static_cast<unsigned long>(ESP.getFreeHeap());
}

const char* ResetReason()
{
    return ResetReasonToString(esp_reset_reason());
}

} // namespace Platform
