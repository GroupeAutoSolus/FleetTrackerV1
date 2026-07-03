#pragma once

#include "CanInterface.h"

class TwaiCanInterface final : public CanInterface {
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
