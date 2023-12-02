//
// Created by Jakub SQTX Sitarczyk on 12/11/2023.
//

#include "controller.h"

static int Controller::btnDetector(const uint8_t CONTROL_BTN_PIN, const uint8_t BTN_LOOP_COOLDOWN,
                                   const uint16_t WAIT_FOR_ANOTHER_CLICK, const uint16_t HOW_LONG_PRESS_BTN) {
  bool btnTimerStarted{false};
  unsigned long startTime{0};

  Serial.println("Use button");

  while(digitalRead(CONTROL_BTN_PIN) == HIGH) {};   // Waiting for first click

  // First click detected
  if(digitalRead(CONTROL_BTN_PIN) == LOW) {
    startTime = {millis()};
    btnTimerStarted = {true};
    while(digitalRead(CONTROL_BTN_PIN) == LOW) {};

    unsigned long pressTime = {millis() - startTime};
    if(pressTime >= HOW_LONG_PRESS_BTN) {
      return ADD_NEW;   // Click and press
    }

    while(btnTimerStarted) {
      unsigned long currTime = {millis() - startTime};
      if(currTime > WAIT_FOR_ANOTHER_CLICK) break;

      // Second click detected
      if(digitalRead(CONTROL_BTN_PIN) == LOW) {
        while(digitalRead(CONTROL_BTN_PIN) == LOW) {};
        return CHOOSE_KEY;  // Double click
      }

      delay(BTN_LOOP_COOLDOWN);
    }

    return GENERATE_TOKEN;  // Single click
  }

  return NONE;  // None click
}


static void Controller::serialFlushCleaner() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}