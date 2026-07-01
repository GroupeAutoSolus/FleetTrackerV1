#pragma once

namespace Diagnostics {

void Initialize();
const char* GetBootStatus();
void LogBootReport();
void LogHeartbeat();

} // namespace Diagnostics
