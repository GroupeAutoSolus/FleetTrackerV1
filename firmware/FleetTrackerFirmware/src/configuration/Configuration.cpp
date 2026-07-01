#include "Configuration.h"

namespace {

Configuration::Settings settings = {
    "GAS-ST-PROTOTYPE-001",
    2000,
    "",
    "",
};

} // namespace

namespace Configuration {

void Load()
{
    // Reserved for future persistent configuration loading and validation.
}

const Settings& Current()
{
    return settings;
}

} // namespace Configuration
