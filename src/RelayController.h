#ifndef RELAY_CONTROLLER_H
#define RELAY_CONTROLLER_H

#include <Arduino.h>

extern bool relayActive[4];

void initRelays();
void handleRelays();
void startFeeding(byte feederId, uint16_t seconds);

#endif // RELAY_CONTROLLER_H
