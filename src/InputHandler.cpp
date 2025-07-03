#include "InputHandler.h"
#include "Settings.h"
#include "FeedingSystem.h"
#include "RelayController.h"
#include "DisplayManager.h"

byte menuLevel = 0;
byte selectedItem = 0;
byte editIndex = 0;
byte editStep = 0;
byte activeFeeder = 0;
byte prevMenu = 0;

void handleEncoder(int8_t dir) {
  switch(menuLevel) {
    case 1: selectedItem = (selectedItem + dir + 4) % 4; break;
    case 2: selectedItem = (selectedItem + dir + numFeedings) % numFeedings; break;
    case 3: selectedItem = (selectedItem + dir + numFeedings) % numFeedings; break;
    case 4: numFeedings = constrain(numFeedings + dir, 1, MAX_FEEDINGS); break;
    case 5:
      if (editStep == 0)
        feedings[editIndex].hour = (feedings[editIndex].hour + 24 + dir) % 24;
      else
        feedings[editIndex].minute = (feedings[editIndex].minute + 60 + dir) % 60;
      break;
    case 6:
      feedings[editIndex].duration = constrain(feedings[editIndex].duration + dir*5, 5, 300);
      break;
    case 7:
      activeFeeder = (activeFeeder + dir + 4) % 4;
      break;
    case 8:
      selectedItem = (selectedItem + dir + 4) % 4;
      break;

  }
}

void handleSelect() {
  switch(menuLevel) {
    case 0:
      menuLevel = 1; selectedItem = 0;
      break;
    case 1:
      prevMenu = menuLevel;
      if (selectedItem == 0) menuLevel = 7;
      else if (selectedItem == 1) { menuLevel = 2; selectedItem = 0; }
      else if (selectedItem == 2) { menuLevel = 3; selectedItem = 0; }
      else if (selectedItem == 3) menuLevel = 4;
      break;
    case 2:
      prevMenu = menuLevel;
      editIndex = selectedItem; editStep = 0; menuLevel = 5;
      break;
    case 3:
      prevMenu = menuLevel;
      editIndex = selectedItem; menuLevel = 6;
      break;
    case 4:
      saveSettings(); menuLevel = 1;
      break;
    case 5:
      if (editStep < 1) editStep++;
      else {
        menuLevel = 8; selectedItem = 0;
      }
      break;
    case 6:
      saveSettings(); menuLevel = 3;
      break;
    case 7:
      if (relayActive[activeFeeder]) {
        relayActive[activeFeeder] = false;
        // сразу гасим
        digitalWrite(RELAY_PIN1 + activeFeeder, LOW);
      } else {
        startFeeding(activeFeeder, feedings[0].duration);
      }
      break;
    case 8:
      // переключаем биты маски для текущего селекта
      feedings[editIndex].feederMask ^= (1 << selectedItem);
      break;
  }
}

void handleBack() {
  switch(menuLevel) {
    case 1: menuLevel = 0; break;
    case 2:
    case 3:
    case 4: menuLevel = 1; break;
    case 5:
    case 8:
      menuLevel = 2;
      saveSettings();
      break;
    case 6:
      menuLevel = 3;
      break;
    case 7:
      menuLevel = 1;
      break;
  }
  selectedItem = 0;
}
