#pragma once

#include "../status/StatusCode.h"

class Module {
public:
    virtual ~Module() = default;

    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual const char* GetName() const = 0;
    virtual StatusCode GetStatus() const = 0;
    virtual StatusCode GetLastError() const = 0;
    virtual bool IsInitialized() const = 0;
};
