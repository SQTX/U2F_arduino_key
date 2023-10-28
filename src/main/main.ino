#include "sha1.h"
#include "TOTP.h"
#include "swRTC.h"

// TODO: Hard-code private key.

// TxT Key: MySimpleSecretTxtKey
// Base32:  JV4VG2LNOBWGKU3FMNZGK5CUPB2EWZLZ
// Hex:     4d7953696d706c655365637265745478744b6579

uint8_t hmacKey[] {0x4d, 0x79, 0x53, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x53, 0x65, 0x63, 0x72, 0x65, 0x74, 0x54, 0x78, 0x74, 0x4b, 0x65, 0x79};

TOTP totp = TOTP(hmacKey, 20);  // hmacKey length
swRTC rtc;                      // TODO: To delete
char code[7];


void setup() {
  Serial.begin(9600);

  rtc.stopRTC();
  // TODO: Hard-code time. RTC is needed!
  rtc.setDate(28, 10, 2023);
  rtc.setTime(19, 24, 0);     // GMT
  rtc.startRTC();
}

void printTime(swRTC *rtc) {
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

void loop() {
  printTime(&rtc);

  long GMT = rtc.getTimestamp();

  Serial.print("TIME: ");
  Serial.println(GMT);

  char* newCode = totp.getCode(GMT);
  if(strcmp(code, newCode) != 0) {
    strcpy(code, newCode);
    Serial.print("Key: ");
    Serial.println(code);
  } 

  Serial.println("=====================");


  delay(30000);   // 30 seconds
}
