# Configuration

## Basic Configuration Parameters

In the main `.ino` file, several constant values have been declared in the configuration section using the `constexpr` operator. \
Changing the values of these constants can affect the configuration of the software itself.

### Hardware

`CONTROL_BTN_PIN` - configuration of **the pin number** to which the **action button is connected**.

* If it is **digital pin 7**, write: \
  `constexpr uint8_t CONTROL_BTN_PIN {7};`

### BTN TIMES

The following parameters relate to the time (in milliseconds) after which the button will detect single operations such as single, double, or long-press clicks.

* `WAIT_FOR_ANOTHER_CLICK` - the maximum **time between the first and second click to detect
  a double-click**. Specify the time in MILLISECONDS.
* `HOW_LONG_PRESS_BTN` - the maximum **time the system will wait for the next (second) click**
  before recognizing a single click. [ms]
* `BTN_LOOP_COOLDOWN` - refresh **time for detecting the second click**. [ms]
  (It's recommended to leave it at the default setting.)

### RTC

**_RTC_** - real-time clock.\
Configuring this element involves calibrating the time set on your **RTC** module to **CET** time,
as the algorithm generating the token operates based on it.

**If the time set on the RTC module does not match** CET time, the **token will be generated with 
a delay or will be incorrect** altogether.

---
The following parameters can be calibrated:
* `TIME_ZONE_OFFSET` - **the difference** (in hours) **between the time zone set on the RTC module
  and CET time**. \
  _Examples:_
    * If you live in **Oslo** and your RTC module has daylight saving time, **the difference
      between CEST (your time) and CET is +2h** \
      `constexpr int8_t TIME_ZONE_OFFSET {2};`
    * If you live in **New York** and your RTC module has the current time, **the difference
      between EST (your time) and CET is -5h** \
      `constexpr int8_t TIME_ZONE_OFFSET {-5};`

* `RTC_OFFSET` - **the difference** (in seconds) **between the time displayed on your computer
  and the time recorded on the RTC module**. Usually, it is a few seconds.
  _Examples:_
    * If your RTC is **delayed by 3 seconds** compared to the computer time, the difference
      is: -3s \
      `constexpr int8_t RTC_OFFSET {-3};`
    * If your RTC is **ahead by 8 seconds** compared to the computer time, the difference
      is: 8s \
      `constexpr int8_t RTC_OFFSET {8};`

## What is a Key

When adding a new key to the database, you will always be asked to provide its name and
the private key itself. All this data should be provided in the form of a String.
* **_Key name_** - any name by which the key will be searched in the database.
* **_Private key_** - a string of characters stored **in Base32 format**.

## Test Configuration

There is an opportunity to test the code's functionality based on keys immediately assigned to the database. To do this:
1. Go to the `example/sampleCodes.cpp` file.
2. Copy the code you are interested in. It can be either a ready-made, simple database with
   2 already assigned keys or code resetting the EEPROM memory (as it would look like
   on the first run of the code).
3. Paste the copied code into the main `.ino` file in the designated areas. \
   For example:
   ```c++
   [...]
   //*******************************
   //! Paste the SampleCode1 here!!!
   String keysDB[4]{"google", "N7QBAAAJUCPUP37V",
                    "github", "AWS4R4HCB5Z54SR2"};
   //*******************************
   [...]
