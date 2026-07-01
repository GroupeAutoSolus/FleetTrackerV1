#include "Mcp2515Module.h"

#include <Arduino.h>
#include <SPI.h>
#include <cstdio>

#include "../../logging/Logger.h"
#include "../../platform/spi/SpiService.h"

namespace {

constexpr uint8_t kInstructionReset = 0xC0;
constexpr uint8_t kInstructionRead = 0x03;
constexpr uint8_t kCanStatRegister = 0x0E;
constexpr uint8_t kConfigurationModeMask = 0x80;
constexpr uint32_t kSpiClockHz = 1000000;
constexpr int kDetectionAttempts = 3;
char logBuffer[128] = {};

enum class ProbeResult {
    Detected,
    Timeout,
    NotResponding,
    UnknownDevice,
};

void LogAttempt(int attempt)
{
    std::snprintf(
        logBuffer,
        sizeof(logBuffer),
        "MCP2515 detection attempt %d of %d",
        attempt,
        kDetectionAttempts);
    Logger::Info(logBuffer);
}

void LogCanStat(uint8_t canstat)
{
    std::snprintf(logBuffer, sizeof(logBuffer), "MCP2515 CANSTAT=0x%02X", canstat);
    Logger::Debug(logBuffer);
}

void SelectDevice()
{
    digitalWrite(SpiService::GetPinConfiguration().defaultChipSelect, LOW);
}

void DeselectDevice()
{
    digitalWrite(SpiService::GetPinConfiguration().defaultChipSelect, HIGH);
}

uint8_t ReadRegister(uint8_t address)
{
    SelectDevice();
    SPI.transfer(kInstructionRead);
    SPI.transfer(address);
    const uint8_t value = SPI.transfer(0x00);
    DeselectDevice();
    return value;
}

ProbeResult ProbeMcp2515()
{
    if (!SpiService::IsInitialized()) {
        Logger::Error("SPI initialization failure.");
        return ProbeResult::Timeout;
    }

    const int chipSelectPin = SpiService::GetPinConfiguration().defaultChipSelect;

    pinMode(chipSelectPin, OUTPUT);
    DeselectDevice();

    SPI.beginTransaction(SPISettings(kSpiClockHz, MSBFIRST, SPI_MODE0));
    SelectDevice();
    SPI.transfer(kInstructionReset);
    DeselectDevice();
    SPI.endTransaction();

    SpiService::DelayAfterPeripheralReset();

    SPI.beginTransaction(SPISettings(kSpiClockHz, MSBFIRST, SPI_MODE0));
    const uint8_t canstat = ReadRegister(kCanStatRegister);
    SPI.endTransaction();

    LogCanStat(canstat);

    if (canstat == 0x00 || canstat == 0xFF) {
        return ProbeResult::NotResponding;
    }

    if ((canstat & kConfigurationModeMask) == kConfigurationModeMask) {
        return ProbeResult::Detected;
    }

    return ProbeResult::UnknownDevice;
}

StatusCode StatusFromProbeResult(ProbeResult result)
{
    switch (result) {
    case ProbeResult::Detected:
        return StatusCode::Ok;
    case ProbeResult::Timeout:
        return StatusCode::Timeout;
    case ProbeResult::NotResponding:
        return StatusCode::HardwareUnavailable;
    case ProbeResult::UnknownDevice:
    default:
        return StatusCode::UnknownDevice;
    }
}

void LogProbeFailure(ProbeResult result)
{
    switch (result) {
    case ProbeResult::Timeout:
        Logger::Error("MCP2515 timeout.");
        break;
    case ProbeResult::NotResponding:
        Logger::Error("MCP2515 not responding.");
        break;
    case ProbeResult::UnknownDevice:
        Logger::Error("Unknown SPI device on MCP2515 chip select.");
        break;
    case ProbeResult::Detected:
        break;
    }
}

} // namespace

void Mcp2515Module::Initialize()
{
    Logger::Info("Initializing MCP2515...");

    initialized = true;

    for (int attempt = 1; attempt <= kDetectionAttempts; ++attempt) {
        LogAttempt(attempt);
        const ProbeResult result = ProbeMcp2515();

        if (result == ProbeResult::Detected) {
            status = StatusCode::Ok;
            lastError = StatusCode::Ok;
            Logger::Info("MCP2515 detected successfully.");
            return;
        }

        lastError = StatusFromProbeResult(result);
        LogProbeFailure(result);
        SpiService::DelayAfterPeripheralReset();
    }

    status = StatusCode::Warning;
    Logger::Error("MCP2515 not detected.");
}

void Mcp2515Module::Update()
{
    // No CAN frame handling in this milestone.
}

const char* Mcp2515Module::GetName() const
{
    return "mcp2515";
}

StatusCode Mcp2515Module::GetStatus() const
{
    return status;
}

StatusCode Mcp2515Module::GetLastError() const
{
    return lastError;
}

bool Mcp2515Module::IsInitialized() const
{
    return initialized;
}
