/*
 * Created by Jakub SQTX Sitarczyk on 21/10/2023.
 * */

// Includes ===========================================================================================================
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

// Configuration ======================================================================================================
//! HARDWARE:
constexpr uint8_t CONTROL_BTN_PIN {7};               //! Set the PIN number to which the action button is connected.

//! BTN TIMES:
constexpr uint16_t WAIT_FOR_ANOTHER_CLICK {500};     //! The maximum time between the first and second click to detect a double-click. Specify the time in MILLISECONDS.
constexpr uint16_t HOW_LONG_PRESS_BTN {1100};        //! The maximum time the system will wait for the next (second) click before recognizing a single click. [ms]
constexpr uint8_t BTN_LOOP_COOLDOWN {15};            //! Refresh time for detecting the second click. (It is recommended to leave it at the default setting.)

//! RTC:
/*! The hour difference between the time zone set to RTC and the UTC time zone [in hours]:
 * CET(summer_time) - UTC = 2 [h]
 * */
constexpr int8_t TIME_ZONE_OFFSET {2};

/*! Time difference between the RTC module time and the real time [in seconds]:
 * 1698601110 - 1698601115 = -5 [s]
 * */
constexpr int8_t RTC_OFFSET {-5};

// RAM of software ====================================================================================================
int numberOfKeys{0};        // The total number of stored keys in memory.
int activeKeyIndex{0};      // Indeks aktualnie aktywnego klucza. Na podstawie tego klucza generowany będzie nowy token
String *keysDatabase{};     // Database

// Define RTC =========================================================================================================
/*! Using the DS3231 RTC module requires its prior configuration and setting of the current time
 * from which the RTC will constantly count up. For this, you can use the DS3231.h library and
 * the DS3231_set example.
 * */
RTClib myRTC;

void genereteToken();
void chooseKey();
void addNewKey();

// Main Arduino functions =============================================================================================
void setup() {
  pinMode(CONTROL_BTN_PIN, INPUT_PULLUP);   // Set a pin of the action button
  Serial.begin(9600);                       // Set band value
  Controller::serialFlushCleaner();        // Clean flush "memory"
  Wire.begin();


  /*!Loading data from the EEPROM memory of the device into RAM.
   * If this is the first run of the program, you will be prompted to prepare the memory for cooperation with
   * the software.
   */
  keysDatabase = DataController::readDataFromEEPROM(&numberOfKeys);


  if (numberOfKeys == 0) {
    Serial.println("No key in memory!");
    Serial.println("Add a new key to memory, please");
    addNewKey();
  } else {
    activeKeyIndex = {1};
  }
}

void loop() {
  delay(5);
  int option = Controller::btnDetector(CONTROL_BTN_PIN, BTN_LOOP_COOLDOWN, WAIT_FOR_ANOTHER_CLICK, HOW_LONG_PRESS_BTN);

  if(option == Controller::GENERATE_TOKEN) {
    genereteToken();
  }
  else if (option == Controller::CHOOSE_KEY) {
    chooseKey();
  }
  else if (option == Controller::ADD_NEW) {
    addNewKey();
  }
  else if (option == Controller::POWEROFF) {
    Serial.println("Power off");
  }
  else {
    Serial.println("None option");
  }

  delay(500);
}


void genereteToken() {
  Serial.print("Active: ");
  Serial.println(keysDatabase[activeKeyIndex-1]);


  String privKey = {keysDatabase[activeKeyIndex]};

//!    Convert StringToChar:
  uint8_t privKeySize = privKey.length();
  char *keyInChar = new char[privKeySize+1];
  privKey.toCharArray(keyInChar, privKeySize+1);

//!    Convert char array to byte array:
  int maxout = base32decode(keyInChar, NULL, 0);
  maxout += 1;
  uint8_t codeInByte[maxout];
  int r = base32decode(keyInChar, codeInByte, maxout);

  delete[] keyInChar;

//!    Cut off all useless numbers after 0:
  uint8_t hmacKey[maxout] = {};
  int cutAfter = {(privKeySize*5)/8};   // Protection against zeros inside the key
  for(int i = 0; i < maxout; i++) {
    if(i >= cutAfter && codeInByte[i] == 0) break;
    hmacKey[i] = codeInByte[i];
  }

//!    Create TOTP object:
  TOTP totp = TOTP(hmacKey, maxout);


//!    Get currently time from RTC module:
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


void chooseKey() {
  Serial.print("Enter a key name: ");

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


  int wantedNameSize = name.length();
  wantedNameSize += 1;
  char *wantedName = new char[wantedNameSize];
  name.toCharArray(wantedName, wantedNameSize);

  bool keyIsFound {false};
  for(int nameIndex = 0; nameIndex < (numberOfKeys*2); nameIndex+=2) {
    String nameFromArr = keysDatabase[nameIndex];
    int currNameSize = nameFromArr.length();
    currNameSize += 1;
    char *currentName = new char[currNameSize];
    nameFromArr.toCharArray(currentName, currNameSize);

    if(strcmp(currentName, wantedName) == 0) {
      keyIsFound = {true};
      activeKeyIndex = {nameIndex+1};

      Serial.println("Key found");
      break;
    }

    delete[] currentName;
  }
  delete[] wantedName;

  if(!keyIsFound) {
    Serial.println("This key does not exist in memory!");
  }
}


void addNewKey() {
  numberOfKeys += 1;      // Increase numbers of all keys in DB

//!    Create new DB with bigger capacity and copy all old data:
  static String *newKeysDB = new String[numberOfKeys*2];
  for(int i = 0; i < (numberOfKeys*2); i++) {
    if(i == ((numberOfKeys*2)-2) || i == ((numberOfKeys*2)-1)){
      newKeysDB[i] = {""};
      continue;
    }
    newKeysDB[i] = keysDatabase[i];
  }
  delete[] keysDatabase;
  keysDatabase = newKeysDB;
  newKeysDB = {nullptr};
  delay(10);

//!    Get new name and new key:
  String newKeyName, newKeyBs32 {};

  Serial.print("Write name of new key: ");
  Controller::serialFlushCleaner();
  while (Serial.available() == 0) {}
  delay(2);
  if (Serial.available() > 0) {
    newKeyName = Serial.readStringUntil('\n');
    newKeyName.trim();
  }
  Serial.println("");
  Serial.print("Name: ");
  Serial.println(newKeyName);

  Serial.print("Write new key in Base32: ");
  Controller::serialFlushCleaner();
  while (Serial.available() == 0) {}
  delay(2);
  if (Serial.available() > 0) {
    newKeyBs32 = Serial.readStringUntil('\n');
    newKeyBs32.trim();
  }
  Serial.println("");
  Serial.print("New key: ");
  Serial.println(newKeyBs32);

//!    Save new data in DB:
  keysDatabase[(numberOfKeys*2)-2] = {newKeyName};
  keysDatabase[(numberOfKeys*2)-1] = {newKeyBs32};

//!    Save new array in EEPROM:
//    Serial.println("Writing new key in memory...");
  DataController::writeDataToEEPROM(keysDatabase, numberOfKeys);
  Serial.println("Done");
}