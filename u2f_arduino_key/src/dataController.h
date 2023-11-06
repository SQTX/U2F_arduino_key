//
// Created by Jakub SQTX Sitarczyk on 06/11/2023.
//

#ifndef U2F_ARDUINO_KEY_DATACONTROLLER_H
#define U2F_ARDUINO_KEY_DATACONTROLLER_H

#include <Arduino.h>
#include <EEPROM.h>

void writeStringToEEPROM(int, const String&);
String readStringFromEEPROM(int);


#endif //U2F_ARDUINO_KEY_DATACONTROLLER_H
