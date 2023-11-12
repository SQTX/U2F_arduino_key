/*
 * Created by Jakub SQTX Sitarczyk on 21/10/2023.
 * */

// Arduino lib:
#include <Wire.h>
#include <DS3231.h>
#include <EEPROM.h>
#include "sha1.h"
#include "TOTP.h"
#include "Base32-Decode.h"
// My file:
#include "src/controller.h"
#include "src/dataConverter.h"
#include "src/dataController.h"


// ******************************************************************
//! Configuration:
//TODO: Add description
constexpr uint8_t CONTROL_BTN_PIN{7};
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
//String keysDB[4]{"github", "JV4VG2LNOBWGKU3FMNZGK5CUPB2EWZLZ",   // "MySimpleSecretTxtKey"
//                 "text", "IFBEGRBRGIZQ===="};                    // "ABCD123"
//                                                                  Base32:
String keysDB[4]{"github", "MySimpleSecretTxtKey",               // "JV4VG2LNOBWGKU3FMNZGK5CUPB2EWZLZ"
                 "text", "ABCD123===="};                         // "IFBEGRBRGIZQ===="

// ******************************************************************
//! RAM memmory:
int numberOfKeys{0};
int activeKeyIndex{1};    // TODO: Change to 0
String *keysDatabase{};
// ******************************************************************
/*! Using the DS3231 RTC module requires its prior configuration and setting of the current time
 * from which the RTC will constantly count up. For this, you can use the DS3231.h library and
 * the DS3231_set example.
 * */
RTClib myRTC;


void setup() {
  pinMode(CONTROL_BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Controller::serialFlushCleaner();        // Clean flush memory
  Wire.begin();

//  NOTE: EEPROM reset:
//  EEPROM.write(0, 'f');
//  EEPROM.write(1, 'o');
//  EEPROM.write(2, 'o');

  // DataController::writeDataToEEPROM(keysDB, 2);
  keysDatabase = DataController::readDataFromEEPROM(&numberOfKeys);


  if (numberOfKeys == 0) {
    Serial.println("No key in memory!");
    Serial.println("The app gets frozen");
    while (true) {};
  }
}


void loop() {
  delay(5);
  int option = Controller::btnDetector(CONTROL_BTN_PIN, BTN_LOOP_COOLDOWN, WAIT_FOR_ANOTHER_CLICK, HOW_LONG_PRESS_BTN);

  if(option == Controller::GENERATE_TOKEN) {
    String usedPrivKey = {keysDatabase[activeKeyIndex]};
    uint8_t * hmacKey = {Converter::convStrToNumArr(&txtusedPrivKeyKey)};


    TOTP totp = TOTP(hmacKey, 20);         // TODO: Hard-code max size of key (use `.length()` on key from array)


    //! Get currently time from RTC module:
    DateTime now{myRTC.now()};                                            // Get current time
    long UnixTimeStep{now.unixtime()};                                    // Replacement in Unix TimeStamp
    long UTC{UnixTimeStep - (TIME_ZONE_OFFSET * 60 * 60) - RTC_OFFSET};


    char *newCode{totp.getCode(UTC)};  // Generate new token

    //! Print token:
    char code[7];
    if (strcmp(code, newCode) != 0) {
      strcpy(code, newCode);
      Serial.print("Token: ");
      Serial.println(code);
    }
  }
  else if (option == Controller::CHOOSE_KEY) {
    Serial.print("Give key name: ");

    String name{};
    Controller::serialFlushCleaner();
    while (Serial.available() == 0) {}
    delay(2);
    if (Serial.available() > 0) {
      name = Serial.readStringUntil('\n');
      name.trim();
    }
    Serial.println("");

    Serial.print("Name: ");
    Serial.println(name);
    Serial.println(name.length());

    for(int nameIndex = 0; nameIndex < (numberOfKeys*2); nameIndex+=2) {
      String nameFromArr = keysDatabase[nameIndex];

      Serial.print(nameFromArr);
      Serial.print(" == ");
      Serial.println(name);
      if(nameFromArr.equals(name)) {
        Serial.println("Jest!");

        activeKeyIndex = nameIndex+1;
        Serial.println(activeKeyIndex);
        break;
      }
    }
  }
  else if (option == Controller::ADD_NEW) {
    Serial.print("Give new key (in Base32): ");

    String newKey{};
    Controller::serialFlushCleaner();
    while (Serial.available() == 0) {}
    delay(2);
    if (Serial.available() > 0) {
      newKey = Serial.readStringUntil('\n');
      newKey.trim();
    }
    Serial.println("");

    Serial.print("New key: ");
    Serial.println(newKey);

    String newForm {};
    base32decodeToString(newKey, newForm);

    Serial.print("New form: ");
    Serial.println(newForm);
  }
  else if (option == Controller::POWEROFF) {
    Serial.println("Power off");
  }
  else {
    Serial.println("None option");
  }

  delay(500);
}
