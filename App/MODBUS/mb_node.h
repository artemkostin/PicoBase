/**
 * @file mb_node.h
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller ModBUS implementation.
 * @version 0.1
 * @date 2021-09-26
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SGP_APPS_MODBUS_NODE
#define SGP_APPS_MODBUS_NODE

#include <stdint.h>
#include <stdio.h>
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "mb_crc.h"
#include "mb_func_proc.h"

#define MODBUS_UART_INTERFACE           uart0
#define MODBUS_UART_SPEED               38400
#define MODBUS_UART_TIMEOUT_US          1000
#define MODBUS_BUFFER_SIZE              256
#define MODBUS_DEFAULT_INVALID_ADDRESS  255

#define MODBUS_FRAME_ADDRESS_OFFSET   0
#define MODBUS_FRAME_FUNCCODE_OFFSET  1
#define MODBUS_FRAME_DATA_OFFSET      2
#define MODBUS_FRAME_MIN_LENGHT       4
#define MODBUS_FRAME_CRC_SIZE         2
#define MODBUS_FRAME_BROADCAST        0

#define MODBUS_ERROR_RESPONSE_CODE_OFFSET 0x80

#define MODBUS_RESPONSE_BUFFER_REDUCTION 3

typedef enum
{
    MODBUS_STATE_IDLE = 0,
    MODBUS_STATE_REQUEST_CHECK,
    MODBUS_STATE_REQUEST_PROCESS,
    MODBUS_STATE_REPLY_NORMAL,
    MODBUS_STATE_REPLY_ERROR,
    MODBUS_STATE_RESPONCE_SENDING,
    MODBUS_STATE_TOTAL
}mbNodeStates_t;

typedef enum
{
    MODBUS_ADU_SUCCESS = 0,
    MODBUS_ADU_MISMATCH_ADDRESS,
    MODBUS_ADU_MISMATCH_CRC,
    MODBUS_ADU_WRONG_FRAME,
    MODBUS_ADU_TOTAL
}mbADUResults_t;

typedef enum
{
    MODBUS_PDU_SUCCESS = 0,
    MODBUS_PDU_ILLIGAL_FUNC =      1,
    MODBUS_PDU_ILLIGAL_DATA_ADDR = 2,
    MODBUS_PDU_ILLIGAL_DATA_VAL  = 3,
    MODBUS_PDU_SRV_DEV_FAILURE =   4,
    MODBUS_PDU_ACK =               5,
    MODBUS_PDU_SRV_DEV_BUSY =      6,
    MODBUS_PDU_TOTAL,
}mbPDUResults_t;

// Modbus Read Coils (01).
// Modbus Read Discrete Inputs (02).
// Modbus Read Holding Registers (03).
// Modbus Read Input Registers (04).
// Modbus Write Single Coil (05).
// Modbus Write Single Register (06).
// Modbus Write Multiple Registers (16).
typedef enum
{
    MODBUS_FUNC_READ_COILS =        (uint8_t)1,
    MODBUS_FUNC_READ_DI =           (uint8_t)2,
    MODBUS_FUNC_READ_HOLD_REG =     (uint8_t)3,
    MODBUS_FUNC_READ_INPUT_REG =    (uint8_t)4,
    MODBUS_FUNC_WRITE_SINGLE_COIL = (uint8_t)5,
    MODBUS_FUNC_WRITE_SINGLE_REG =  (uint8_t)6,
    MODBUS_FUNC_WRITE_MULTI_REG =   (uint8_t)16,
    MODBUS_FUNC_TOTAL
}mbFunc_t;

typedef struct
{
    uint8_t* data;
    uint16_t crc;
    uint16_t data_size;
    uint8_t  address;
    uint8_t  func_code;
}mbADUFrame_t;

void AppModBUS_Init(uint8_t address);
void AppModBUS_Run(void);
void AppModBUS_SetAddress(uint8_t address);

#endif //SGP_APPS_MODBUS_NODE