#include "Platform.h"

#include <Arduino.h>

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

} // namespace Platform
