//
// Created by Jakub Sitarczyk on 12/11/2023.
//

#ifndef U2F_ARDUINO_KEY_CONTROLLER_H
#define U2F_ARDUINO_KEY_CONTROLLER_H

#include <Arduino.h>

class Controller {
public:
  enum {
    NONE = -1,
    POWEROFF = 0,
    GENERATE_TOKEN,
    CHOOSE_KEY,
    ADD_NEW
  };

  static int btnDetector(const uint8_t CONTROL_BTN_PIN, const uint8_t BTN_LOOP_COOLDOWN,
                         const uint16_t WAIT_FOR_ANOTHER_CLICK, const uint16_t HOW_LONG_PRESS_BTN);

  static void serialFlushCleaner();
};


#endif //U2F_ARDUINO_KEY_CONTROLLER_H
