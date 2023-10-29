#include "swRTC.h"
#include "sha1.h"
#include "TOTP.h"
#include "Base32-Decode.h"


// ******************************************************************
// Configuration:
constexpr uint8_t KEY_SIZE = 30;


// ******************************************************************
// Function dec:
void printTime(swRTC*);
String convBase32ToTxt(String);
uint8_t* convStrToNumArr(String*);


// ******************************************************************
// Example database with Base32 format keys:
String keysDB[2] {"JV4VG2LNOBWGKU3FMNZGK5CUPB2EWZLZ",
                  "IFBEGRBRGIZQ===="};

// Txt keys: "MySimpleSecretTxtKey", "ABCD123"


// ******************************************************************
swRTC rtc;                      // TODO: To delete


void setup() {
  Serial.begin(9600);

  // Hard-code setting of the current GMT time
  rtc.stopRTC();

  rtc.setDate(29, 10, 2023);
  rtc.setTime(14, 34, 30);  // GMT
  rtc.startRTC();
}


void loop() {
  // Choose a key:
  String usedPrivKey {keysDB[0]};   // TODO: Hard-code key index

  String txtKey {convBase32ToTxt(usedPrivKey)};
  uint8_t* hmacKey {convStrToNumArr(&txtKey)};
  TOTP totp = TOTP(hmacKey, 20);    // TODO: Hard-code size of key

  char code[7];


  // Get Unix TimesSteps: 
  long GMT = rtc.getTimestamp();

  printTime(&rtc);

  Serial.print("TIME: ");
  Serial.println(GMT);


  char* newCode = totp.getCode(GMT);  // Generate new token

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

String convBase32ToTxt(String in) {
  String out;

  int r = base32decodeToString(in, out);
  if (r < 0) {
    Serial.println("Could not decode string");
    return;
  }
  
  return out;
}

uint8_t* convStrToNumArr(String* txt) {
  static uint8_t NumArr[KEY_SIZE]{};

  for (uint8_t i = 0; i < KEY_SIZE; i++) {
    char c = txt->charAt(i);
    NumArr[i] = static_cast<uint8_t>(c);
  }
  return NumArr;
}
