#include "RTCManager.h"

RTC_DS3231 rtc;

void initRTC() {
  rtc.begin();
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
