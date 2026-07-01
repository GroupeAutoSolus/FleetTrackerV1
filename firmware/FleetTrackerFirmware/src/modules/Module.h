#pragma once

enum class ModuleStatus {
    NotInitialized,
    Ok,
    Warning,
    Error,
};

class Module {
public:
    virtual ~Module() = default;

    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual const char* GetName() const = 0;
    virtual ModuleStatus GetStatus() const = 0;
    virtual const char* GetLastError() const = 0;
};
