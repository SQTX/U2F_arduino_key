//
// Created by Jakub SQTX Sitarczyk on 06/11/2023.
//

#include "dataController.h"

static void DataController::writeDataToEEPROM(String *keys, const int numberOfKeys, const int MAX_SIZE) {
  int addresIndex {0};

  addPrefixToEEPROM(&addresIndex);
  writeIntToEEPROM(&addresIndex, numberOfKeys);
  writeIntToEEPROM(&addresIndex, MAX_SIZE);

  if(numberOfKeys == 0) {
    ;
  } else {
//    Serial.println("DEBUG: Saving is in processing");
    for(int i = 0; i < (numberOfKeys*2); i++) {
      uint8_t txtSize = keys[i].length() + 1;
      writeIntToEEPROM(&addresIndex, txtSize);
      writeStringToEEPROM(&addresIndex, keys[i]);
    }
  }
//  Serial.println("DEBUG: Saving complited!");
}

static String* DataController::readDataFromEEPROM(int *numberOfKeys) {
  int addresIndex {0};
//  Serial.println("DEBUG: Reading is in processing");

  if(prefixExist(&addresIndex)) {
//    Serial.println("DEBUG: Prefix is correct");

    uint8_t keysNumber = readIntFromEEPROM(&addresIndex);
    (*numberOfKeys) = keysNumber;
    uint8_t maxEEPROMSize = readIntFromEEPROM(addresIndex++);
//    addresIndex++;

    static String *keys = new String[keysNumber*2];

    for(int i = 0; i < keysNumber*2; i++) {
      uint8_t txtSize = readIntFromEEPROM(&addresIndex);
      keys[i] = readStringFromEEPROM(&addresIndex, txtSize);
    }

//    Serial.println("DEBUG: Reading complited!");
    return keys;
  }else {
    Serial.println("FATAL ERROR: EEPROM memory is not preper to colaborate with \"U2F_arduino_key\" soft!");
    Serial.println("Do you want to preper EEPROM memory to colaborate with this soft? (Y/n)");
    Serial.println("WARNING: Data which are in EEPROM memory currently could be overwriet!");

    bool decisionMade {false};
    do{
      char c {'n'};

      Serial.print("Do you agree: ");
      Controller::serialFlushCleaner();
      while(Serial.available() == 0) {}
      delay(2);
      if(Serial.available() > 0) {
        c = Serial.read();
      }
      Serial.println("");


      if(c == 'Y') {
        writeDataToEEPROM(nullptr, 0);
        decisionMade = {true};
      }else if(c == 'n') {
        Serial.println("The app gets frozen");
        while(true) {};                           // NOTE: Infinited loop!
        decisionMade = {true};
      }else {
        Serial.println("Wrong character! Try again.");
        decisionMade = {false};
      }
    }while(!decisionMade);

    static String *keys = new String[0];
//    Serial.println("DEBUG: Reading complited!");
    return keys;    // Return empty array
  }
}


//Priv --------------------------------------------------------------------------------
static void DataController::addPrefixToEEPROM(int *addrOffset){
  writeStringToEEPROM(addrOffset, EEPROM_PREFIX, false);
}

static bool DataController::prefixExist(int *addrOffset){
//  Serial.println("DEBUG: Prefix is checking");
  const uint8_t prefixSize = EEPROM_PREFIX.length();
  String currentPrefix = readStringFromEEPROM(addrOffset, prefixSize);

  char *currentPrefixArr = new char[prefixSize+1];
  char *goodPrefixArr = new char[prefixSize+1];
  currentPrefix.toCharArray(currentPrefixArr, prefixSize+1);
  EEPROM_PREFIX.toCharArray(goodPrefixArr, prefixSize+1);

  if(strcmp(currentPrefixArr, goodPrefixArr) == 0) {
    delete[] currentPrefixArr;
    delete[] goodPrefixArr;
    return true;
  }
  else {
    delete[] currentPrefixArr;
    delete[] goodPrefixArr;
    return false;
  }
}


static void DataController::writeIntToEEPROM(int *addrOffset, const int number) {
  EEPROM.write(*addrOffset, number);
  (*addrOffset)++;
}

static int DataController::readIntFromEEPROM(int *addrOffset) {
  int number = EEPROM.read(*addrOffset);
  (*addrOffset)++;
  return number;
}


static void DataController::writeStringToEEPROM(int *addrOffset, const String &txt, bool nullChar) {
  uint8_t size = txt.length();

  for (int i = 0; i < size; i++) {
    EEPROM.write((*addrOffset) + i, txt[i]);
  }
  (*addrOffset) += size;

  if(nullChar){
    EEPROM.write((*addrOffset), '\0');
    (*addrOffset)++;
  }
}

static String DataController::readStringFromEEPROM(int *addrOffset, int size, bool nullChar) {
//  char data[size + 1];
  char *data = new char[size];

  for (int i = 0; i < size; i++) {
    data[i] = EEPROM.read((*addrOffset) + i);
  }
  (*addrOffset) += size;

  if(nullChar) {
    data[size] = '\0';
    (*addrOffset)++;
  }

  String txt = data;
  delete[] data;
  return txt;
}
