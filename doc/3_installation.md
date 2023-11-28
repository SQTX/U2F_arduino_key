# Installation

## Before Installation

Before proceeding with the download and installation of the U2F_arduino_key project, 
it is **advisable to prepare Arduino IDE** since it will be used to upload and run the code 
on the board.

## Step-by-Step Installation

1. Download/clone the project from the official repository,
2. Open the file with the extension `.ino` (`u2f_arduino_key.ino`) using Arduino IDE,
3. Connect the Arduino board to the USB port and select the appropriate board model in the 
opened IDE,
4. Upload the required libraries to Arduino IDE:
   * `TOTP library` by Luca Dentella - [link](https://github.com/lucadentella/TOTP-Arduino),
   * `DS3231` by Andrew Wickert - [link](https://github.com/NorthernWidget/DS3231),
   * `Base32-Decode` by Dirk-Willem von Gulik - 
   [link](https://github.com/dirkx/Arduino-Base32-Decode),
5. If you want to make any changes in the initial code configuration, it is recommended to 
check [here](https://github.com/SQTX/U2F_arduino_key/wiki/4_Configuration),
6. After running the program (_clicking the arrow icon_), the software will be loaded onto 
the board. To read the message displayed by Arduino, open the _Serial Monitor_ 
(`Tools -> Serial Monitor`) and ensure that the baud rate is set to the same value as specified 
in the code here.
7. During the first run, you may receive a message about _EEPROM_ memory mismatch with the 
software. Allow the device to adapt the memory for operation. \
**WARNING**: Data stored in _EEPROM_ memory will be overwritten!
8. **That's it!**

The software has been uploaded, and the circuit is ready to operate.\
To learn how to use it, refer to the 
[user manual](https://github.com/SQTX/U2F_arduino_key/wiki/5_Manual).