#include "ModuleManager.h"

#include <cstdio>

namespace {

bool initialized = false;
StatusCode status = StatusCode::NotInitialized;
StatusCode lastError = StatusCode::Ok;
char statusSummary[128] = {};

const char* BoolToYesNo(bool value)
{
    return value ? "yes" : "no";
}

void UpdateStatusSummary()
{
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
    // Future milestones will register and initialize hardware-backed modules here.
    initialized = true;
    status = StatusCode::Ok;
    lastError = StatusCode::Ok;
    UpdateStatusSummary();
}

void Update()
{
    // Future milestones will update registered modules here.
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
