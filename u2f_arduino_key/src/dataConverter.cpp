/*
 * Created by Jakub SQTX Sitarczyk on 28/10/2023.
 * */

#include "dataConverter.h"


String Converter::convBase32ToTxt(String* in) {
  String out {};

  int r {base32decodeToString(*in, out)};
  if (r < 0) {
    Serial.println("String is not detected!");
    return;
  }
  
  return out;
}


uint8_t* Converter::convStrToNumArr(String* txt) {
  static uint8_t NumArr[KEY_SIZE] {};

  for (uint8_t i {0}; i < KEY_SIZE; i++) {
    char c {txt->charAt(i)};
    NumArr[i] = {static_cast<uint8_t>(c)};
  }

  return NumArr;
}
