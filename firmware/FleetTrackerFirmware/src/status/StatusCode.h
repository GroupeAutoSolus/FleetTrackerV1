#pragma once

enum class StatusCode {
    Ok,
    Warning,
    Error,
    NotInitialized,
    Timeout,
    HardwareUnavailable,
};

const char* StatusCodeToString(StatusCode statusCode);
