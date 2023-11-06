//
// Created by Jakub Sitarczyk on 06/11/2023.
//

#ifndef U2F_ARDUINO_KEY_KEY_H
#define U2F_ARDUINO_KEY_KEY_H

#include <Arduino.h>

class Key {
public:
  Key(String, String);
  ~Key();

  const String &Key::getName() const;
  void Key::setName(const String &);

  const String &Key::getKey() const;
  void Key::setKey(const String &);

private:
  String m_name;
  String m_keyBase32;
};


#endif //U2F_ARDUINO_KEY_KEY_H
