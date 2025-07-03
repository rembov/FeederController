#include "DisplayManager.h"
#include "Settings.h"
#include "FeedingSystem.h"
#include "InputHandler.h"
#include "RelayController.h"
extern LiquidCrystal_I2C lcd;

void updateDisplay(DateTime now) {
  static unsigned long lastUpdate = 0;
  static unsigned long lastDisplayChange = 0;
  static bool blinkState = false;
  static bool showFeedCount = true;
  static byte prevMenuLevel = 255;

  if (millis() - lastUpdate < 500) return;
  lastUpdate = millis();

  if (menuLevel != prevMenuLevel) {
    lcd.clear();
    prevMenuLevel = menuLevel;
  }

  switch(menuLevel) {
    case 0: {
      if (millis() - lastDisplayChange > 2000) {
        showFeedCount = !showFeedCount;
        lastDisplayChange = millis();
        lcd.clear();
      }
      lcd.setCursor(0,0);
      lcd.print("Time: ");
      print2digits(now.hour());
      lcd.print(':');
      print2digits(now.minute());
      lcd.setCursor(0,1);
      if (showFeedCount) {
        lcd.print("Feedings: ");
        lcd.print(numFeedings);
      } else {
        lcd.print("Next: ");
        DateTime next = getNextFeeding(now);
        if (next.hour() == 24) {
          lcd.print("--:--");
        } else {
          print2digits(next.hour());
          lcd.print(':');
          print2digits(next.minute());
        }
      }
      break;
    }
    case 1: {
      const char* items[4] = {"Manual","Time","Portion","Count"};
      for (byte row=0; row<2; row++) {
        for (byte col=0; col<2; col++) {
          byte idx = row*2 + col;
          lcd.setCursor(col*9 + (idx%2?1:0), row);
          lcd.print(selectedItem==idx ? ">" : " ");
          lcd.print(items[idx]);
        }
      }
      break;
    }
    case 2: {
      lcd.setCursor(0,0);
      lcd.print("Set time #");
      lcd.print(selectedItem+1);
      lcd.setCursor(0,1);
      print2digits(feedings[selectedItem].hour);
      lcd.print(':');
      print2digits(feedings[selectedItem].minute);
      break;
    }
    case 3: {
      lcd.setCursor(0,0);
      lcd.print("Portion #");
      lcd.print(selectedItem+1);
      lcd.setCursor(0,1);
      lcd.print(feedings[selectedItem].duration);
      lcd.print(" sec");
      break;
    }
    case 4: {
      lcd.setCursor(0,0);
      lcd.print("Feedings count:");
      lcd.setCursor(0,1);
      lcd.print("> ");
      lcd.print(numFeedings);
      lcd.print(" <");
      break;
    }
    case 5: {
      lcd.setCursor(0,0);
      lcd.print("Time #");
      lcd.print(editIndex+1);
      lcd.setCursor(0,1);
      if (millis() % 1000 < 500) {
        if (editStep == 0) { lcd.print("  "); }
        else { print2digits(feedings[editIndex].hour); }
      } else {
        print2digits(feedings[editIndex].hour);
      }
      lcd.print(':');
      if (millis() % 1000 < 500) {
        if (editStep == 1) { lcd.print("  "); }
        else { print2digits(feedings[editIndex].minute); }
      } else {
        print2digits(feedings[editIndex].minute);
      }
      break;
    }
    case 6: {
      lcd.setCursor(0,0);
      lcd.print("Portion #");
      lcd.print(editIndex+1);
      lcd.setCursor(0,1);
      lcd.print("> ");
      lcd.print(feedings[editIndex].duration);
      lcd.print(" sec <");
      break;
    }
      case 7: {
  lcd.setCursor(0, 0);
  lcd.print("Manual Feeding  "); 
  lcd.setCursor(0, 1);
  char statusLine[17];
  snprintf(statusLine, sizeof(statusLine), "> Feeder %d %s", 
           activeFeeder + 1, 
           relayActive[activeFeeder] ? "ON " : "OFF");
  
  lcd.print(statusLine);
  byte len = strlen(statusLine);
  for(byte i = len; i < 16; i++) {
    lcd.print(' ');
  }
  break;}
    case 8: {
      lcd.setCursor(0,0);
      lcd.print("Feeders for #");
      lcd.print(editIndex+1);
      lcd.setCursor(0,1);
      for (byte i=0; i<4; i++) {
        lcd.print(i==selectedItem ? '>' : ' ');
        lcd.print(i+1);
        lcd.print(feedings[editIndex].feederMask & (1<<i) ? 'X' : '_');
        lcd.print(' ');
      }
      break;
    }
  }

  // рисуем индикаторы активных реле
  for (byte i=0; i<4; i++) {
    if (relayActive[i]) {
      lcd.setCursor(15 - i, 0);
      lcd.print('*');
    }
  }
}

void print2digits(byte number) {
  if (number < 10) lcd.print('0');
  lcd.print(number);
}
