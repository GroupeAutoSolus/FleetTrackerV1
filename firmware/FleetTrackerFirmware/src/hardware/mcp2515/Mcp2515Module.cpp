#include "Mcp2515Module.h"

#include <Arduino.h>
#include <SPI.h>

#include "../../logging/Logger.h"
#include "../../platform/spi/SpiService.h"

namespace {

constexpr uint8_t kInstructionReset = 0xC0;
constexpr uint8_t kInstructionRead = 0x03;
constexpr uint8_t kCanStatRegister = 0x0E;
constexpr uint8_t kConfigurationModeMask = 0x80;
constexpr uint32_t kSpiClockHz = 1000000;

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

bool ProbeMcp2515()
{
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

    return (canstat & kConfigurationModeMask) == kConfigurationModeMask;
}

} // namespace

void Mcp2515Module::Initialize()
{
    Logger::Info("Initializing MCP2515...");

    initialized = true;

    if (ProbeMcp2515()) {
        status = StatusCode::Ok;
        lastError = StatusCode::Ok;
        Logger::Info("MCP2515 detected successfully.");
        return;
    }

    status = StatusCode::Error;
    lastError = StatusCode::HardwareUnavailable;
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
