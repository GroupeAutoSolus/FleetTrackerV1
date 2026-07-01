#pragma once

#include "../status/StatusCode.h"

namespace ModuleManager {

void Initialize();
void Update();
const char* GetStatusSummary();
StatusCode GetStatus();
StatusCode GetLastError();
bool IsInitialized();

} // namespace ModuleManager
