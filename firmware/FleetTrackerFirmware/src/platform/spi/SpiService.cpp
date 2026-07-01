#include "SpiService.h"

#include <SPI.h>
#include <cstdio>

#include "../Platform.h"

namespace {

constexpr SpiService::PinConfiguration kDefaultPins = {
    18,
    19,
    23,
    5,
    4,
};

char pinSummary[96] = {};
bool initialized = false;

} // namespace

namespace SpiService {

void Initialize()
{
    SPI.begin(
        kDefaultPins.sck,
        kDefaultPins.miso,
        kDefaultPins.mosi,
        kDefaultPins.defaultChipSelect);

    initialized = true;

    std::snprintf(
        pinSummary,
        sizeof(pinSummary),
        "SCK=GPIO%d,MISO=GPIO%d,MOSI=GPIO%d,CS=GPIO%d,MCP2515_INT=GPIO%d",
        kDefaultPins.sck,
        kDefaultPins.miso,
        kDefaultPins.mosi,
        kDefaultPins.defaultChipSelect,
        kDefaultPins.futureMcp2515Interrupt);
}

bool IsInitialized()
{
    return initialized;
}

const PinConfiguration& GetPinConfiguration()
{
    return kDefaultPins;
}

const char* GetPinConfigurationSummary()
{
    return pinSummary;
}

void DelayAfterPeripheralReset()
{
    Platform::Delay(10);
}

} // namespace SpiService
