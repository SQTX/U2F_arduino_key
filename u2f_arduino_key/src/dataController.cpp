//
// Created by Jakub SQTX Sitarczyk on 06/11/2023.
//

#include "dataController.h"





//Priv --------------------------------------------------------------------------------
void writeStringToEEPROM(int addrOffset, const String &txt) {
  byte size = txt.length();

  EEPROM.write(addrOffset, size);  // Save size of String
//  Save String:
  for (int i = 0; i < size; i++) {
    EEPROM.write(addrOffset + 1 + i, txt[i]);
  }
}

String readStringFromEEPROM(int addrOffset) {
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];

  for (int i = 0; i < newStrLen; i++) {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';

  return String(data);
}
