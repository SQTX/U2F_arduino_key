//
// Created by Jakub Sitarczyk on 06/11/2023.
//

#include "Key.h"

Key::Key(String name = "", String key = "") {
 this->m_name = {name};
 this->m_keyBase32 = {key};
}
Key::~Key() {}

const String &Key::getName() const {
  return m_name;
}
void Key::setName(const String &name) {
  Key::m_name = name;
}

const String &Key::getKey() const {
  return m_keyBase32;
}
void Key::setKey(const String &key) {
  Key::m_keyBase32 = key;
}