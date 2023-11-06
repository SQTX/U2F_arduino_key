//
// Created by Jakub SQTX Sitarczyk on 06/11/2023.
//

#ifndef U2F_ARDUINO_KEY_DATACONTROLLER_H
#define U2F_ARDUINO_KEY_DATACONTROLLER_H

#include <Arduino.h>
#include <EEPROM.h>
#include "Key.h"


void writeIntToEEPROM(int, const int);
int readIntFromEEPROM(int);

void writeStringToEEPROM(int, const String&);
String readStringFromEEPROM(int, int);

void writeKeyToEEPROM(int, const Key&);
Key readKeyFromEEPROM(int);

#endif //U2F_ARDUINO_KEY_DATACONTROLLER_H
