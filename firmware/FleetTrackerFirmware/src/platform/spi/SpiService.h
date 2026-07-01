#pragma once

namespace SpiService {

struct PinConfiguration {
    int sck;
    int miso;
    int mosi;
    int defaultChipSelect;
    int futureMcp2515Interrupt;
};

void Initialize();
bool IsInitialized();
const PinConfiguration& GetPinConfiguration();
const char* GetPinConfigurationSummary();
void DelayAfterPeripheralReset();

} // namespace SpiService
