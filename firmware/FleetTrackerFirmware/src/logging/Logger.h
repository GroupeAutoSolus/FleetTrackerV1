#pragma once

namespace Logger {

void Initialize();
void Info(const char* message);
void Warn(const char* message);
void Error(const char* message);
void Debug(const char* message);

} // namespace Logger
