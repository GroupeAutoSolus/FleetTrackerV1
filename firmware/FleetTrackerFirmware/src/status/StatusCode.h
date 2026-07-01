#pragma once

enum class StatusCode {
    Ok,
    Warning,
    Error,
    NotInitialized,
    Timeout,
    HardwareUnavailable,
    UnknownDevice,
};

const char* StatusCodeToString(StatusCode statusCode);
