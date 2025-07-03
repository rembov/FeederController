#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include <Arduino.h>
extern byte menuLevel;
extern byte selectedItem;
extern byte editIndex;
extern byte editStep;
extern byte activeFeeder;
void handleEncoder(int8_t dir);
void handleSelect();
void handleBack();
#endif
