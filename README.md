# PicoBase
This is repository for SmartGardenProject pot controller.

# Software design overview
For all detailed descriptions, please refer to Documentation folder.
**ToDo:** Add description for other SW components.

## 1. Command Line Interface (CLI)
In order to be able to set up device properly, it is important to have some direct CLI. In SPG pot it is implemented by text-based, AT command, protocol for the following commands:
 - AT+REBOOT - Reboot the device.
 - AT+INFO [GET|SET] <INFO_ID> <VALUE> - Get or Set device information.
 - AT+PARAM [GET|SET] <PARAM_ID> <VALUE> - Get or Set database value.
 - AT+MODBUS - Switch to a regular operation mode, MODBus server.
 - AT+AUTH - Authentificate session (Not implemented yet).

## 2. Regular operation mode: MODBus RTU server
To make this device compatible with industrial Programmable Logic Controlers (PLC), the MODBus RTU protocol is using.
**ToDo:** Registers map description will added.

## 3. Databse
Database in current project is built around EEPROM memory.

# Hardware design overview
For all detailed descriptions, please refer to Documentation folder.
**ToDo:** Add description for other HW components.

## 1. Target platform
Raspberry Pi PICO was selected as platform that have a lot of IO compatibilities and scalable memory amount.

## 2. EEPROM (for Database)
HW-111 module is used it has AT24C32 (EEPROM) and DS1307 (RTC).

## 3. RS485
RS485 selected as a hardware protocol for MODBus RTU.
