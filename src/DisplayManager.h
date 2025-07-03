#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

void updateDisplay(DateTime now);
void print2digits(byte number);

#endif // DISPLAY_MANAGER_H
