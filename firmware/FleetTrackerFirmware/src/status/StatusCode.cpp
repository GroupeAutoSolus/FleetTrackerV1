#include "StatusCode.h"

const char* StatusCodeToString(StatusCode statusCode)
{
    switch (statusCode) {
    case StatusCode::Ok:
        return "OK";
    case StatusCode::Warning:
        return "WARNING";
    case StatusCode::Error:
        return "ERROR";
    case StatusCode::NotInitialized:
        return "NOT_INITIALIZED";
    case StatusCode::Timeout:
        return "TIMEOUT";
    case StatusCode::HardwareUnavailable:
        return "HARDWARE_UNAVAILABLE";
    case StatusCode::UnknownDevice:
        return "UNKNOWN_DEVICE";
    default:
        return "ERROR";
    }
}
