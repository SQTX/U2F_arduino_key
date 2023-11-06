//
// Created by Jakub SQTX Sitarczyk on 06/11/2023.
//

#include "dataController.h"





//Priv --------------------------------------------------------------------------------
void writeIntToEEPROM(int addrOffset, const int number) {
  EEPROM.write(addrOffset, number);
}

int readIntFromEEPROM(int addrOffset) {
  int number = EEPROM.read(addrOffset);
  return number;
}


void writeStringToEEPROM(int addrOffset, const String &txt) {
  byte size = txt.length();

  for (int i = 0; i < size; i++) {
    EEPROM.write(addrOffset + 1 + i, txt[i]);
  }
}

String readStringFromEEPROM(int addrOffset, int size) {
  char data[size + 1];

  for (int i = 0; i < size; i++) {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[size] = '\0';

  return String(data);
}


void writeKeyToEEPROM(int addrOffset, const Key &key) {
  String nameTxt = key.getName();
  String keyTex = key.getKey();

  uint8_t nameSize = nameTxt.length();
  uint8_t keySize = keyTex.length();

  writeIntToEEPROM(addrOffset, nameSize);
  writeIntToEEPROM(addrOffset+1, keySize);
  writeStringToEEPROM(addrOffset+2, nameTxt);
  writeStringToEEPROM(addrOffset+2+nameSize, nameTxt);
}

Key readKeyFromEEPROM(int addrOffset) {
  uint8_t nameSize = readIntFromEEPROM(addrOffset);
  uint8_t keySize = readIntFromEEPROM(addrOffset+1);

  String nameTxt = readStringFromEEPROM(addrOffset+2, nameSize);
  String keyTex = readStringFromEEPROM(addrOffset+2+nameSize, keySize);

  Key key(nameTxt, keyTex);
  return key;
}
