/*
 * Created by Jakub SQTX Sitarczyk on 21/10/2023.
 * */

// Arduino lib:
#include <Wire.h>
#include <DS3231.h>
#include "sha1.h"
#include "TOTP.h"
// My file:
#include "src/dataConverter.h"


// ******************************************************************
// Configuration:
// constexpr uint8_t KEY_SIZE {30};       //TODO:  Moved to dataConverter.h

  /* The hour difference between the time zone set to RTC and the UTC time zone [in hours]:
   * CET(summer_time) - UTC = 2 [h]
   * */
  constexpr int8_t TIME_ZONE_OFFSET {2};
  /* Time difference between the RTC module time and the real time [in seconds]:
   * 1698601110 - 1698601115 = -5 [s]
   * */
  constexpr int8_t RTC_OFFSET {-5};       //
                                          //


// ******************************************************************
// Example database with Base32 format keys:
String keysDB[2] {"JV4VG2LNOBWGKU3FMNZGK5CUPB2EWZLZ",   // "MySimpleSecretTxtKey"
                  "IFBEGRBRGIZQ===="};                  // "ABCD123"


// ******************************************************************
/* Using the DS3231 RTC module requires its prior configuration and setting of the current time
 * from which the RTC will constantly count up. For this, you can use the DS3231.h library and
 * the DS3231_set example.
 * */
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


  // Get currently time from RTC module:
  DateTime now {myRTC.now()};           // Get current time
  long UnixTimeStep {now.unixtime()};   // Replacement in Unix TimeStamp
  //   UTC = (local_time - TIME_ZONE_OFFSET - RTC_OFFSET)
  long UTC {UnixTimeStep - (TIME_ZONE_OFFSET*60*60) - RTC_OFFSET};

//  Serial.print("TIME: ");
//  Serial.println(UTC);


  char* newCode {totp.getCode(UTC)};  // Generate new token

  // Print token
  if (strcmp(code, newCode) != 0) {
    strcpy(code, newCode);
    Serial.print("Token: ");
    Serial.println(code);
  }
  Serial.println("==============");


  // Dynamic refresh (Always every 00' and 30' seconds)
  uint16_t restTime {(30 - (UTC % 30)) * 1000};
  delay(restTime);
}
