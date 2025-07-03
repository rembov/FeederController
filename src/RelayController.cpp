#include "RelayController.h"
#include "Settings.h"

const byte relayPins[4] = {RELAY_PIN1, RELAY_PIN2, RELAY_PIN3, RELAY_PIN4};
unsigned long relayStartTimes[4]  = {0};
unsigned long relayDurations[4]   = {0};
bool relayActive[4] = {false};

void initRelays() {
  for (byte i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }
}

void handleRelays() {
  for (byte i = 0; i < 4; i++) {
    if (relayActive[i] && millis() - relayStartTimes[i] >= relayDurations[i]) {
      digitalWrite(relayPins[i], LOW);
      relayActive[i] = false;
    }
  }
}

void startFeeding(byte feederId, uint16_t seconds) {
  digitalWrite(relayPins[feederId], HIGH);
  relayStartTimes[feederId] = millis();
  relayDurations[feederId]  = (unsigned long)seconds * 1000;
  relayActive[feederId]     = true;
}
