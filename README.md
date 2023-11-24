# U2F_Arduino_Key

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![License: MIT](https://img.shields.io/badge/C%2B%2B-5487C7?style=flat)](https://opensource.org/licenses/MIT)\
[![arduino-library-badge](https://www.ardu-badge.com/badge/TOTP-library.svg)](https://www.arduino.cc/reference/en/libraries/totp-library/)
[![arduino-library-badge](https://www.ardu-badge.com/badge/Base32-Decode.svg)](https://www.arduino.cc/reference/en/libraries/base32-decode/)
[![arduino-library-badge](https://www.ardu-badge.com/badge/DS3231.svg)](https://www.arduino.cc/reference/en/libraries/ds3231/)\


## Description
The project consists of ready-to-use software and a schematic for building *the dual-verification key* itself. 
The operating principle is inspired by keys created by _Yubico_.\
(_Presented project was created for a university course._)

By creating a circuit similar to the one presented in the documentation and utilizing the software provided here, 
it is possible to develop a personal, more affordable alternative to a U2F key.

[//]: # (<img align="center" src="https://i.ibb.co/C7ZN55V/u2f-key-v1.jpg" width="400" height="400"/>)
<img src="https://i.ibb.co/C7ZN55V/u2f-key-v1.jpg" alt="u2f-key-v1"  width="400" height="400" border="0">

---
### WARNING
This project has been created solely for educational and hobbyist purposes. 
I personally do not recommend using it as an actual form of protecting accounts or data. 
Consider it more as an interesting experiment and something to test in your own secure environment.

If you genuinely need a U2F key to protect your assets, it is better to consider purchasing a certified device.
For example, one like: [Yubico-Amazon](https://www.amazon.com/Yubico-YubiKey-USB-Authentication-Security/dp/B07HBD71HL)

## Documentation
**The complete project documentation can be found in the Wiki tab** on the project's GitHub page.
[Wiki-Link](https://github.com/SQTX/U2F_arduino_key/wiki)

**In it, you can find, among other things:**
* Full schematic of the electronic circuit,
* List of all necessary libraries,
* Detailed description of the key configuration,
* Description of all major functionalities with explanations.

## Technical Details
A detailed breakdown of the modules used has been presented in the documentation, 
along with how they are connected.

**Modules utilized in the project include, among others:**
* _Arduino UNO R4_,
* RTC _DS3231_ module.\
  (The project requires a pre-configured electronic RTC module for proper functioning, 
  as the Arduino itself doesn't have a built-in RTC.)

## MIT License
More information can be found here: [Link](https://github.com/SQTX/U2F_arduino_key/blob/main/LICENSE)