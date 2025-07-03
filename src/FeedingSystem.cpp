#include "FeedingSystem.h"
#include <EEPROM.h>
#include "Settings.h"

Feeding feedings[MAX_FEEDINGS];
byte numFeedings = 1;

void saveSettings() {
  EEPROM.write(0, numFeedings);
  for (byte i = 0; i < numFeedings; i++) {
    EEPROM.write(1 + i*5, feedings[i].hour);
    EEPROM.write(2 + i*5, feedings[i].minute);
    EEPROM.write(3 + i*5, highByte(feedings[i].duration));
    EEPROM.write(4 + i*5, lowByte(feedings[i].duration));
    EEPROM.write(5 + i*5, feedings[i].feederMask);
  }
  EEPROM.write(100, 2); // версия
}

void loadSettings() {
  numFeedings = EEPROM.read(0);
  if (numFeedings < 1 || numFeedings > MAX_FEEDINGS) numFeedings = 1;
  
  byte version = EEPROM.read(100);
  for (byte i = 0; i < numFeedings; i++) {
    feedings[i].hour       = EEPROM.read(1 + i*5);
    feedings[i].minute     = EEPROM.read(2 + i*5);
    feedings[i].duration   = word(EEPROM.read(3 + i*5), EEPROM.read(4 + i*5));
    if (version == 2) {
      feedings[i].feederMask = EEPROM.read(5 + i*5);
    } else {
      byte oldId = EEPROM.read(5 + i*5);
      if (oldId > 3) oldId = 0;
      feedings[i].feederMask = 1 << oldId;
    }
  }
  if (version != 2) saveSettings();
}

void checkFeeding(DateTime now) {
  for (byte i = 0; i < numFeedings; i++) {
    if (now.hour() == feedings[i].hour &&
        now.minute() == feedings[i].minute) {
      extern void startFeeding(byte, uint16_t);
      for (byte j = 0; j < 4; j++) {
        if (feedings[i].feederMask & (1 << j)) {
          startFeeding(j, feedings[i].duration);
        }
      }
    }
  }
}

DateTime getNextFeeding(DateTime now) {
  uint32_t nowTs = now.unixtime();
  uint32_t bestTs = 0xFFFFFFFF;
  DateTime next(2000,1,1,24,0,0);

  for (byte d = 0; d < 2; d++) {
    DateTime dayBase = now + TimeSpan(d,0,0,0);
    for (byte i = 0; i < numFeedings; i++) {
      DateTime cand(dayBase.year(), dayBase.month(), dayBase.day(),
                    feedings[i].hour, feedings[i].minute, 0);
      uint32_t ts = cand.unixtime();
      if (ts > nowTs && ts < bestTs) {
        bestTs = ts;
        next = cand;
      }
    }
  }
  return next;
}
