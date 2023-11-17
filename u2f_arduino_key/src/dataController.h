//
// Created by Jakub SQTX Sitarczyk on 06/11/2023.
//

#ifndef U2F_ARDUINO_KEY_DATACONTROLLER_H
#define U2F_ARDUINO_KEY_DATACONTROLLER_H

#include <Arduino.h>
#include <EEPROM.h>


class DataController {
public:
  /*! The main function that saves data on the EEPROM memory. The following are transferred to memory:
   * prefix - allowing you to check whether the EEPROM is already adapted to work with the application,
   * numberOfKeys - number of all saved keys,
   * MAX_SIZE - maximum number of keys that can be saved in EEPROM,
   * keys - an array of keys with their names.
   * */
  static void writeDataToEEPROM(String *keys, const int numberOfKeys, const int MAX_SIZE = MAX_EEPROM_CAPACITY);

  /*! A function that checks whether the memory is suitable for the application.
   * If so, it downloads all the keys with their names and assigns them to RAM.
   * If not, it allows you to initialize new memory or freezes the application completely.
   * As an argument, we pass a reference to the container storing the total number of all saved keys.
   * */
  static String *readDataFromEEPROM(int *numberOfKeys);

private:
  static constexpr int MAX_EEPROM_CAPACITY{30};
  static inline String EEPROM_PREFIX{"sqx"};

  static void addPrefixToEEPROM(int *);

  static bool prefixExist(int *);

  static void writeIntToEEPROM(int *, const int);

  static int readIntFromEEPROM(int *);

  static void writeStringToEEPROM(int *, const String &, bool nullChar = true);

  static String readStringFromEEPROM(int *, int, bool nullChar = false);

  static void serialFlush();
};


#endif //U2F_ARDUINO_KEY_DATACONTROLLER_H
