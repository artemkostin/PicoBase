/**
 * @file mb_func_proc.h
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller ModBUS implementation.
 * @version 0.1
 * @date 2021-10-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SGP_APPS_MODBUS_FUNC_PROC
#define SGP_APPS_MODBUS_FUNC_PROC

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "mb_crc.h"

#define MODBUS_COILS_COUNT_MIN 0x0001
#define MODBUS_COILS_COUNT_MAX 0x07D0

#define MODBUS_DI_COUNT_MIN 0x0001
#define MODBUS_DI_COUNT_MAX 0x07D0

#define MODBUS_HOLDING_REG_COUNT_MIN 0x0001
#define MODBUS_HOLDING_REG_COUNT_MAX 0x007D

#define MODBUS_INPUT_REG_COUNT_MIN 0x0001
#define MODBUS_INPUT_REG_COUNT_MAX 0x007D

#define MODBUS_HOLDING_REG_WRITE_COUNT_MIN 0x0001
#define MODBUS_HOLDING_REG_WRITE_COUNT_MAX 0x007B
#define MODBUS_HOLDING_REG_WRITE_RESP_SIZE 4

typedef enum
{
    MODBUS_FUNC_RESULT_SUCCESS = 0,
    MODBUS_FUNC_RESULT_TOTAL
}mbFuncRet_t;

typedef enum
{
    MODBUS_FUNC_CHECK_SUCCESS = 0,
    MODBUS_FUNC_CHECK_INVALID_AMOUNT = 2,
    MODBUS_FUNC_CHECK_INVALID_QUANTITY = 3,
    MODBUS_FUNC_CHECK_TOTAL
}mbFuncCheckRet_t;

mbFuncCheckRet_t ModBUSFunc_ReadCoils(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx);
mbFuncCheckRet_t ModBUSFunc_ReadDiscreteInput(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx);
mbFuncCheckRet_t ModBUSFunc_ReadHoldingReg(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx);
mbFuncCheckRet_t ModBUSFunc_ReadInputReg(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx);
mbFuncCheckRet_t ModBUSFunc_WriteSingleCoil(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx);
mbFuncCheckRet_t ModBUSFunc_WriteSingleReg(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx);
mbFuncCheckRet_t ModBUSFunc_WriteMultiReg(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx);

#endif //SGP_APPS_MODBUS_FUNC_PROC