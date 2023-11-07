//
// Created by Jakub SQTX Sitarczyk on 06/11/2023.
//

#include "dataController.h"

static void DataController::writeDataToEEPROM(String *keys, const int numberOfKeys, const int MAX_SIZE) {
  int addresIndex {0};
  writeIntToEEPROM(&addresIndex, numberOfKeys);
  writeIntToEEPROM(&addresIndex, MAX_SIZE);

  if(numberOfKeys == 0) {
    ;
  } else {
    Serial.println("Saving in processing");
    for(int i = 0; i < (numberOfKeys*2); i++) {
      uint8_t txtSize = keys[i].length() + 1;
      writeIntToEEPROM(&addresIndex, txtSize);
      writeStringToEEPROM(&addresIndex, keys[i]);
    }
    Serial.println("Save Complited!");
  }
}

static String* DataController::readDataFromEEPROM(int *numberOfKeys) {
  int addresIndex {0};

  uint8_t keysNumber = readIntFromEEPROM(&addresIndex);
  (*numberOfKeys) = keysNumber;
//  uint8_t maxEEPROMSize = readIntFromEEPROM(addresIndex++);
  addresIndex++;

  static String *keys = new String[keysNumber*2];

  for(int i = 0; i < keysNumber*2; i++) {
    uint8_t txtSize = readIntFromEEPROM(&addresIndex);
    keys[i] = readStringFromEEPROM(&addresIndex, txtSize);

    Serial.println(keys[0]);
    Serial.println(keys[1]);
  }

  return keys;
}


//Priv --------------------------------------------------------------------------------
static void DataController::writeIntToEEPROM(int *addrOffset, const int number) {
  EEPROM.write(*addrOffset, number);
  (*addrOffset)++;
}

static int DataController::readIntFromEEPROM(int *addrOffset) {
  int number = EEPROM.read(*addrOffset);
  (*addrOffset)++;
  return number;
}


static void DataController::writeStringToEEPROM(int *addrOffset, const String &txt) {
  uint8_t size = txt.length();

  for (int i = 0; i < size; i++) {
    EEPROM.write((*addrOffset) + i, txt[i]);
  }
  (*addrOffset) += size;

  EEPROM.write((*addrOffset), '\0');
  (*addrOffset)++;
}

static String DataController::readStringFromEEPROM(int *addrOffset, int size) {
//  char data[size + 1];
  char data[size];

  for (int i = 0; i < size; i++) {
    data[i] = EEPROM.read((*addrOffset) + i);
  }

//  data[size] = '\0';

  (*addrOffset) += size;
  return String(data);
}
