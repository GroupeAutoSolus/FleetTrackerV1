#include "ModuleManager.h"

namespace {

constexpr const char* kNoModulesRegistered = "no hardware modules registered";

} // namespace

namespace ModuleManager {

void Initialize()
{
    // Future milestones will register and initialize hardware-backed modules here.
}

void Update()
{
    // Future milestones will update registered modules here.
}

const char* GetStatusSummary()
{
    return kNoModulesRegistered;
}

} // namespace ModuleManager
