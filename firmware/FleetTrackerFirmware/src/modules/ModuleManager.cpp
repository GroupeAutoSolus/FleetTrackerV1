#include "ModuleManager.h"

#include <cstdio>

#include "../hardware/mcp2515/Mcp2515Module.h"

namespace {

bool initialized = false;
StatusCode status = StatusCode::NotInitialized;
StatusCode lastError = StatusCode::Ok;
char statusSummary[128] = {};
Mcp2515Module mcp2515Module;
Module* modules[] = {
    &mcp2515Module,
};

constexpr int kModuleCount = sizeof(modules) / sizeof(modules[0]);

const char* BoolToYesNo(bool value)
{
    return value ? "yes" : "no";
}

void UpdateStatusSummary()
{
    if (kModuleCount > 0) {
        std::snprintf(
            statusSummary,
            sizeof(statusSummary),
            "Module{name=%s,status=%s,last_error=%s,initialized=%s}",
            modules[0]->GetName(),
            StatusCodeToString(modules[0]->GetStatus()),
            StatusCodeToString(modules[0]->GetLastError()),
            BoolToYesNo(modules[0]->IsInitialized()));
        return;
    }

    std::snprintf(
        statusSummary,
        sizeof(statusSummary),
        "ModuleManager{name=module_manager,status=%s,last_error=%s,initialized=%s,registered_modules=0}",
        StatusCodeToString(status),
        StatusCodeToString(lastError),
        BoolToYesNo(initialized));
}

} // namespace

namespace ModuleManager {

void Initialize()
{
    initialized = true;
    status = StatusCode::Ok;
    lastError = StatusCode::Ok;

    for (int i = 0; i < kModuleCount; ++i) {
        modules[i]->Initialize();
        if (modules[i]->GetStatus() == StatusCode::Error) {
            status = StatusCode::Warning;
            lastError = modules[i]->GetLastError();
        }
    }

    UpdateStatusSummary();
}

void Update()
{
    for (int i = 0; i < kModuleCount; ++i) {
        modules[i]->Update();
    }

    UpdateStatusSummary();
}

const char* GetStatusSummary()
{
    return statusSummary;
}

StatusCode GetStatus()
{
    return status;
}

StatusCode GetLastError()
{
    return lastError;
}

bool IsInitialized()
{
    return initialized;
}

} // namespace ModuleManager
