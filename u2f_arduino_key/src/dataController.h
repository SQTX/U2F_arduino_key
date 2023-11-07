//
// Created by Jakub SQTX Sitarczyk on 06/11/2023.
//

#ifndef U2F_ARDUINO_KEY_DATACONTROLLER_H
#define U2F_ARDUINO_KEY_DATACONTROLLER_H

#include <Arduino.h>
#include <EEPROM.h>


class DataController {
public:
  static void writeDataToEEPROM(String *, int, int);

  static String *readDataFromEEPROM(int *);

private:
  static void writeIntToEEPROM(int *, const int);

  static int readIntFromEEPROM(int *);

  static void writeStringToEEPROM(int *, const String &);

  static String readStringFromEEPROM(int *, int);
};


#endif //U2F_ARDUINO_KEY_DATACONTROLLER_H
