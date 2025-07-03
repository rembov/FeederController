#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "src/Settings.h"
#include "src/FeedingSystem.h"
#include "src/RelayController.h"
#include "src/InputHandler.h"
#include "src/DisplayManager.h"
#include "src/RTCManager.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);

  initRTC();
  initRelays();
  loadSettings();
}

void loop() {
  static int8_t lastCLK = digitalRead(CLK);
  int8_t newCLK = digitalRead(CLK);
  if (newCLK != lastCLK && newCLK == LOW) {
    int8_t dir = (digitalRead(DT) != newCLK) ? 1 : -1;
    handleEncoder(dir);
  }
  lastCLK = newCLK;

  static bool buttonPressed = false;
  static unsigned long lastDebounce = 0;
  if (digitalRead(SW) == LOW) {
    if (!buttonPressed && millis() - lastDebounce > 50) {
      buttonPressed = true;
      lastDebounce = millis();
    }
  } else if (buttonPressed) {
    buttonPressed = false;
    unsigned long pressDuration = millis() - lastDebounce;
    if (pressDuration > 1500) handleBack();
    else if (pressDuration > 50) handleSelect();
  }

  static byte lastMinute = 255;
  DateTime now = rtc.now();
  if (now.minute() != lastMinute) {
    lastMinute = now.minute();
    checkFeeding(now);
  }

  updateDisplay(now);
  handleRelays();
}

