//
// Created by Jakub SQTX Sitarczyk on 06/11/2023.
//

#ifndef U2F_ARDUINO_KEY_DATACONTROLLER_H
#define U2F_ARDUINO_KEY_DATACONTROLLER_H

#include <Arduino.h>
#include <EEPROM.h>


class DataController {
public:
  static void writeDataToEEPROM(String*, int, int);
  static String* readDataFromEEPROM(int*);

private:
  static constexpr int MAX_EEPROM_CAPACITY {30};
  static inline String EEPROM_PREFIX {"sqx"};

  static void addPrefixToEEPROM(int *addrOffset);
  static bool prefixExist(int *addrOffset);

  static void writeIntToEEPROM(int*, const int);
  static int readIntFromEEPROM(int*);

  static void writeStringToEEPROM(int*, const String&, bool nullChar = true);
  static String readStringFromEEPROM(int*, int, bool nullChar = false);

  static void serialFlush();
};


#endif //U2F_ARDUINO_KEY_DATACONTROLLER_H
