/*
 * Created by Jakub SQTX Sitarczyk on 21/10/2023.
*/

// Arduino lib:
#include <Wire.h>
#include <DS3231.h>
#include "sha1.h"
#include "TOTP.h"
// My file:
#include "src/dataConverter.h"


// ******************************************************************
// Configuration:
// constexpr uint8_t KEY_SIZE = 30;   // Moved to dataConverter.h
  constexpr int8_t RTC_OFFSET = 5;   // Time difference between the real time time and the RTC module [in seconds]: (Real_time - RTC)


// ******************************************************************
// Example database with Base32 format keys:
String keysDB[2] {"JV4VG2LNOBWGKU3FMNZGK5CUPB2EWZLZ",   // "MySimpleSecretTxtKey"
                  "IFBEGRBRGIZQ===="};                  // "ABCD123"


// ******************************************************************
RTClib myRTC;


void setup() {
  Serial.begin(9600);
  Wire.begin();
}


void loop() {  
  // Choose a key:
  String usedPrivKey {keysDB[0]};   // TODO: Hard-code key index

  String txtKey {Converter::convBase32ToTxt(&usedPrivKey)};
  uint8_t* hmacKey {Converter::convStrToNumArr(&txtKey)};
  TOTP totp = TOTP(hmacKey, 20);    // TODO: Hard-code size of key

  char code[7];


  // RTC:
  DateTime now {myRTC.now()};   // Get current time from RTC module
  long UnixTimeStep {now.unixtime()};
  //   UTC = CET(summer_time) - 2h + RTC_OFFSET
  long UTC {UnixTimeStep - (2*60*60) + RTC_OFFSET};

  Serial.print("TIME: ");
  Serial.println(UTC);


  char* newCode {totp.getCode(UTC)};  // Generate new token

  // Print token
  if (strcmp(code, newCode) != 0) {
    strcpy(code, newCode);
    Serial.print("Token: ");
    Serial.println(code);
  }
  Serial.println("===========================");


  // Dynamic refresh (Always every 00' and 30' seconds)
  uint16_t restTime {(30 - (UTC % 30)) * 1000};
  delay(restTime);
}
