#include "Logger.h"

#include <Arduino.h>

#include "../platform/Platform.h"

namespace {

constexpr unsigned long kSerialBaudRate = 115200;
constexpr unsigned long kSerialReadyTimeoutMs = 3000;

void WriteLogLine(const char* level, const char* message)
{
    Serial.print('[');
    Serial.print(level);
    Serial.print("] ");
    Serial.println(message);
}

} // namespace

namespace Logger {

void Initialize()
{
    Serial.begin(kSerialBaudRate);

    const unsigned long startedAtMs = Platform::Millis();
    while (!Serial && (Platform::Millis() - startedAtMs) < kSerialReadyTimeoutMs) {
        Platform::Delay(10);
    }
}

void Info(const char* message)
{
    WriteLogLine("INFO", message);
}

void Warn(const char* message)
{
    WriteLogLine("WARN", message);
}

void Error(const char* message)
{
    WriteLogLine("ERROR", message);
}

void Debug(const char* message)
{
    WriteLogLine("DEBUG", message);
}

} // namespace Logger
