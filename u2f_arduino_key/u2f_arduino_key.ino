/*
 * Created by Jakub SQTX Sitarczyk on 21/10/2023.
 * */

// Arduino lib:
#include <Wire.h>
#include <DS3231.h>
#include <EEPROM.h>
#include "sha1.h"
#include "TOTP.h"
// My file:
#include "src/controller.h"
#include "src/dataConverter.h"
#include "src/dataController.h"


// ******************************************************************
//! Configuration:
//TODO: Add description
constexpr uint8_t CONTROL_BTN_PIN {7};
constexpr uint8_t BTN_LOOP_COOLDOWN {15};   // Second-click-loop delay
constexpr uint16_t WAIT_FOR_ANOTHER_CLICK {500};       // Time how long sys will be waiting to detected second click
constexpr uint16_t HOW_LONG_PRESS_BTN {1100};       // Time how long sys will be waiting to detected second click

/*! The hour difference between the time zone set to RTC and the UTC time zone [in hours]:
 * CET(summer_time) - UTC = 2 [h]
 * */
constexpr int8_t TIME_ZONE_OFFSET {2};

/*! Time difference between the RTC module time and the real time [in seconds]:
 * 1698601110 - 1698601115 = -5 [s]
 * */
constexpr int8_t RTC_OFFSET {-5};
// ******************************************************************
// Example database with Base32 format keys:
String keysDB[4]{"github", "JV4VG2LNOBWGKU3FMNZGK5CUPB2EWZLZ",   // "MySimpleSecretTxtKey"
                 "text", "IFBEGRBRGIZQ===="};                    // "ABCD123"

// ******************************************************************
//! RAM memmory:
int numberOfKeys{0};
String *keysDatabase{};
// ******************************************************************
/*! Using the DS3231 RTC module requires its prior configuration and setting of the current time
 * from which the RTC will constantly count up. For this, you can use the DS3231.h library and
 * the DS3231_set example.
 * */
RTClib myRTC;

void serialFlush();



//int btnDetector();

void generateToken();

void chooseKey();

void addNewKey();


void setup() {
  pinMode (CONTROL_BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  serialFlush();        // Clean flush memory
  Wire.begin();

//  NOTE: EEPROM reset:
//  EEPROM.write(0, 'f');
//  EEPROM.write(1, 'o');
//  EEPROM.write(2, 'o');

//  DataController::writeDataToEEPROM(keysDB, 2);
  keysDatabase = DataController::readDataFromEEPROM(&numberOfKeys);


  if (numberOfKeys == 0) {
    Serial.println("No key in memory!");
    Serial.println("The app gets frozen");
    while (true) {};
  }
}



void loop() {
  switch(Controller::btnDetector(CONTROL_BTN_PIN, BTN_LOOP_COOLDOWN, WAIT_FOR_ANOTHER_CLICK, HOW_LONG_PRESS_BTN)){
    case Controller::GENERATE_TOKEN:
      generateToken();
      break;
    case Controller::CHOOSE_KEY:
      Serial.println("Choose");
      break;
    case Controller::ADD_NEW:
      Serial.println("Add");
      break;
    case Controller::POWEROFF:
      Serial.println("Power off");
      break;
    default:
      Serial.println("None option");
      break;
  }
  delay(500);
}






void generateToken() {
  String usedPrivKey{keysDatabase[1]};   // TODO: Hard-code key index

  String txtKey{Converter::convBase32ToTxt(&usedPrivKey)};
  uint8_t * hmacKey{Converter::convStrToNumArr(&txtKey)};
  TOTP totp = TOTP(hmacKey, 20);         // TODO: Hard-code max size of key (use `.length()` on key from array)

  char code[7];


  // Get currently time from RTC module:
  DateTime now{myRTC.now()};           // Get current time
  long UnixTimeStep{now.unixtime()};   // Replacement in Unix TimeStamp
  //   UTC = (local_time - TIME_ZONE_OFFSET - RTC_OFFSET)
  long UTC{UnixTimeStep - (TIME_ZONE_OFFSET * 60 * 60) - RTC_OFFSET};

//  Serial.print("TIME: ");
//  Serial.println(UTC);


  char *newCode{totp.getCode(UTC)};  // Generate new token

  // Print token
  if (strcmp(code, newCode) != 0) {
    strcpy(code, newCode);
    Serial.print("Token: ");
    Serial.println(code);
  }
  Serial.println("==============");


  //! Dynamic refresh (Always every 00' and 30' seconds)
//  uint16_t restTime{(30 - (UTC % 30)) * 1000};
//  delay(restTime);
}


void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}
