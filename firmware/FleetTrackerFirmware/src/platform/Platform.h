#pragma once

namespace Platform {

void Initialize();
unsigned long Millis();
void Delay(unsigned long milliseconds);
unsigned long FreeHeapBytes();
const char* ResetReason();

} // namespace Platform
