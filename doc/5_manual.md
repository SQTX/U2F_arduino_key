# Manual

## Control

The circuit is controlled by the user through the connected and configured 
[here](https://github.com/SQTX/U2F_arduino_key/wiki/4_Configuration) action button. 
The appropriate combination of clicks allows triggering one of the three possible 
operating functions.

### Operating Modes and Activation

1. **Single-click button** the function to **display tokens using the currently active key**. 
In the default configuration, the active key will always be the first one stored in memory.
2. **Double-clicking button** the function to **choose a saved/added private key on the device**. 
We search for it using the name set during addition (`key-name` & `key`). \
If the **key is found, the index of the active key will be changed**, and the token-displaying 
function will refer to the newly selected key. \
If the **key does not exist in the user's database, they will be informed about it**.
3. **Pressing and holding the button** (min. 1sec) will trigger the function to **add a new key**. 
The user will be prompted to enter (via the _terminal_/_serial monitor_ in the Arduino IDE) 
the key's name (by which it will be sought) and the private key **IN BASE32 FORMAT** (_i.e., 
directly provided by the applications - **you don't have to change anything, just transcribe 
it from the page**_). \
The newly added key will be automatically saved in the EEPROM memory of the circuit.

### Quick Table
| Operation           | Function              |
|---------------------|-----------------------|
| Single Click        | Display Token         |
| Double Click        | Search and Activate Key|
| Click and Hold      | Add a New Key         |