#pragma once

namespace Configuration {

struct Settings {
    const char* deviceId;
    unsigned long heartbeatIntervalMs;
    const char* futureApn;
    const char* futureServerUrl;
};

void Load();
const Settings& Current();

} // namespace Configuration
