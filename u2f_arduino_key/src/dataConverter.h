/*
 * Created by Jakub SQTX Sitarczyk on 28/10/2023.
*/

#ifndef U2F_ARDUINO_KEY_DATACONVERTER_H
#define U2F_ARDUINO_KEY_DATACONVERTER_H

// Arduino lib:
#include <Arduino.h>
#include "Base32-Decode.h"


constexpr uint8_t KEY_SIZE = 30;

class Converter {
public:

  static String convBase32ToTxt(String*);

  static uint8_t* convStrToNumArr(String*);
};


#endif //U2F_ARDUINO_KEY_DATACONVERTER_H
