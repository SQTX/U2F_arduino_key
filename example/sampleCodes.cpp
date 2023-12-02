//
// Created by Jakub SQTX Sitarczyk on 01/12/2023.
//

//! Copy and paste the code snippets provided here into the main `.ino` file in the designated areas.

// The SampleCode1: ***************************************************************************************************
/*! An array containing two existing keys for two different applications.
 * It allows for quick filling of the device memory to test the correctness of the key
 * generation mechanism and the data storage and retrieval system.
 */

String keysDB[4]{"google", "N7QBAAAJUCPUP37V",
                 "github", "AWS4R4HCB5Z54SR2"};

//! Example of a third key (do not copy):
//               "fb",     "JBSWY3DPEHPK3PXP"


// The SampleCode2: ***************************************************************************************************
/*! Function allowing a complete reset of the EEPROM memory by overwriting the prefix.
 * By pasting the following line of code, the initialization and preparation of the EEPROM memory
 * for operation with the code will be executed.
 * Important: Apply the above line once and remove it afterward;
 * otherwise, the memory will be reset with each execution.
 */

EEPROM.write(0, 'f');


/*! Function saving the previously added (in SampleCode1) database of existing keys, keysDB, in EEPROM memory.
 * If you have added new keys to the database, change the second parameter of the function to the total number
 * of keys (only keys; the name and key together form one key).
 * The line resetting the EEPROM above is NOT needed.
 */
DataController::writeDataToEEPROM(keysDB, 2);