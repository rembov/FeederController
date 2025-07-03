#ifndef FEEDING_SYSTEM_H
#define FEEDING_SYSTEM_H
#include <RTClib.h>
#include "Settings.h"
struct Feeding { uint8_t hour, minute; uint16_t duration; byte feederMask; };
extern Feeding feedings[MAX_FEEDINGS];
extern byte numFeedings;
void checkFeeding(DateTime now);
DateTime getNextFeeding(DateTime now);
void saveSettings();
void loadSettings();
#endif
