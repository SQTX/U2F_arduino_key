/*
 * Created by Jakub SQTX Sitarczyk on 21/10/2023.
*/

// Arduino lib:
#include "swRTC.h"
#include "sha1.h"
#include "TOTP.h"
// My file:
#include "dataConverter.h"


// ******************************************************************
// Configuration:
// constexpr uint8_t KEY_SIZE = 30;   // Moved to dataConverter.h


// ******************************************************************
// Example database with Base32 format keys:
String keysDB[2] {"JV4VG2LNOBWGKU3FMNZGK5CUPB2EWZLZ",   // "MySimpleSecretTxtKey"
                  "IFBEGRBRGIZQ===="};                  // "ABCD123"


// ******************************************************************
swRTC rtc;                      // TODO: To delete


void setup() {
  Serial.begin(9600);

  
  // Hard-code setting of the current GMT time
  rtc.stopRTC();

  rtc.setDate(29, 10, 2023);
  rtc.setTime(15, 45, 30);  // GMT
  rtc.startRTC();
}


void loop() {
  // Choose a key:
  String usedPrivKey {keysDB[0]};   // TODO: Hard-code key index

  String txtKey {Converter::convBase32ToTxt(&usedPrivKey)};
  uint8_t* hmacKey {Converter::convStrToNumArr(&txtKey)};
  TOTP totp = TOTP(hmacKey, 20);    // TODO: Hard-code size of key

  char code[7];


  // Get Unix TimesSteps: 
  long GMT = rtc.getTimestamp();

  printTime(&rtc);

  Serial.print("TIME: ");
  Serial.println(GMT);


  char* newCode {totp.getCode(GMT)};  // Generate new token

  // Print it
  if (strcmp(code, newCode) != 0) {
    strcpy(code, newCode);
    Serial.print("Key: ");
    Serial.println(code);
  }


  Serial.println("===========================");
  delay(30000);  // TODO: Hard-code 30 seconds
}


// ******************************************************************
// Function def:
void printTime(swRTC* rtc) {
  Serial.print("Clock: ");
  Serial.print(rtc->getDay());
  Serial.print('-');
  Serial.print(rtc->getMonth());
  Serial.print('-');
  Serial.print(rtc->getYear());
  Serial.print(' ');
  Serial.print(rtc->getHours());
  Serial.print(':');
  Serial.print(rtc->getMinutes());
  Serial.print(':');
  Serial.println(rtc->getSeconds());
}
