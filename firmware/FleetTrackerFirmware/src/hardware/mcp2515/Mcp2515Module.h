#pragma once

#include "../../modules/Module.h"

class Mcp2515Module final : public Module {
public:
    void Initialize() override;
    void Update() override;
    const char* GetName() const override;
    StatusCode GetStatus() const override;
    StatusCode GetLastError() const override;
    bool IsInitialized() const override;

private:
    bool initialized = false;
    StatusCode status = StatusCode::NotInitialized;
    StatusCode lastError = StatusCode::NotInitialized;
};
