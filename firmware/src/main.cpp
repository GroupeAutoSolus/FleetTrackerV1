#include "FleetTracker/Application.hpp"

int main()
{
    fleettracker::Application app;
    app.initialize();
    app.runOnce();
    return 0;
}
