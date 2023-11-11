/*
 * Created by Jakub SQTX Sitarczyk on 28/10/2023.
 * */

#ifndef U2F_ARDUINO_KEY_DATACONVERTER_H
#define U2F_ARDUINO_KEY_DATACONVERTER_H

// Arduino lib:
#include <Arduino.h>
#include "Base32-Decode.h"

//! Constant maximum hard-code key size
constexpr uint8_t KEY_SIZE = 30;

class Converter {
public:
  /*! Function that converts a String variable in Base32 format
   * into a string variable in text format.
   * */
  static String convBase32ToTxt(String*);
  /*! Function that converts a String variable in text format
   * into an array of bytes in decimal format.
   * */
  static uint8_t* convStrToNumArr(String*);

};

#endif //U2F_ARDUINO_KEY_DATACONVERTER_H
