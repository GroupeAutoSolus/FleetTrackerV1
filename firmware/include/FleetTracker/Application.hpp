#pragma once

namespace fleettracker {

class Application {
public:
    Application() = default;

    void initialize();
    void runOnce();
};

} // namespace fleettracker
