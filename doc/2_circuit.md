# Circuit

## Compatibility

The presented software is compatible with the following versions of Arduino boards:
* Arduino UNO R3, 
* ~~Arduino Leonardo~~ (**_not yet_**),
* ~~Digispark Attiny85~~.

## What You Need

To build the circuit, you will need the following components:

* Arduino board (one of the mentioned above), 
* RTC DS3231 module, 
* button, 
* resistors:
  * (1x) 1,000 k<span>Ω</span>,
  * (1x) 10,000 k<span>Ω</span>, 
* capacitor: (1x) 100 <span>µ</span>F, 
* wires.

## DIY

Now, all you need to do is connect everything as shown below.

### Circuit Diagram

<p align="center">
  <img src="https://github.com/SQTX/U2F_arduino_key/blob/doc/img/circuit_diagram.png" width="500">
</p>

### Instructions

As seen in the above diagram, the circuit required for operation is very simple. 
It only requires connecting the RTC module (in this case, DS3231) and the button. 
To avoid interference on the button, it is advisable to add an RC filter to it.

#### RTC:

| Arduino | DS3231 |
|---------|--------|
| SCL     | SCL    |
| SDA     | SDA    |
| 5V      | VCC    |
| GND     | GND    |

Before connecting the RTC, it is recommended to configure it using dedicated libraries.

---

#### Button + RC Filter:

The lower part of the diagram shows the connection of the button in "pull-up" mode with 
a built-in RC filter. \

<p align="center">
  <img src="https://github.com/SQTX/U2F_arduino_key/blob/doc/img/btn+rc.png">
</p>

The final connection of the button to pin D7 is optional, but changing it will require 
adjustments in the software configuration. \
Learn more about this [here](https://github.com/SQTX/U2F_arduino_key/wiki/4_Configuration).