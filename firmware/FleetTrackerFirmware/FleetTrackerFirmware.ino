constexpr unsigned long kHeartbeatIntervalMs = 2000;

unsigned long lastHeartbeatMs = 0;

void setup()
{
    Serial.begin(115200);

    while (!Serial && millis() < 3000) {
        delay(10);
    }

    Serial.println("GAS Smart Tracker booting...");
}

void loop()
{
    const unsigned long nowMs = millis();

    if (nowMs - lastHeartbeatMs >= kHeartbeatIntervalMs) {
        lastHeartbeatMs = nowMs;
        Serial.println("GAS Smart Tracker heartbeat");
    }
}
