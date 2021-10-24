/**
 * @file mb_func_proc.c
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller ModBUS implementation.
 * @version 0.1
 * @date 2021-10-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "mb_func_proc.h"

//All coils read as zero value.
mbFuncCheckRet_t ModBUSFunc_ReadCoils(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx)
{
    mbFuncCheckRet_t return_value = MODBUS_FUNC_CHECK_SUCCESS;
    uint16_t start_address = *(buffer_rx + 1) | (*(buffer_rx) << 8);
    uint16_t coils_count =   *(buffer_rx + 3) | (*(buffer_rx + 2) << 8);
    if(MODBUS_COILS_COUNT_MIN <= coils_count && coils_count <= MODBUS_COILS_COUNT_MAX)
    {
        if(start_address >= 0x0000 && ((start_address + coils_count) <= 0xFFFF))
        {
            uint16_t byte_count = (uint16_t)((coils_count + 7) / 8);
            *(buffer_tx) = byte_count;
            memset((void*)(buffer_tx + 1), 0x00, byte_count);
            *data_size_tx = byte_count + 1;
            printf("MODBUS_FUNC_READ_COILS: %04x @ %04x\r\n", coils_count, start_address);
        }
        else
        {
            *data_size_tx = 0;
            return_value = MODBUS_FUNC_CHECK_INVALID_AMOUNT;
        }
    }
    else
    {
        *data_size_tx = 0;
        return_value = MODBUS_FUNC_CHECK_INVALID_QUANTITY;
    }
    printf("MODBUS_FUNC_READ_COILS: Exit with: %02d\r\n", return_value);
    return return_value;
}

mbFuncCheckRet_t ModBUSFunc_ReadDiscreteInput(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx)
{
    mbFuncCheckRet_t return_value = MODBUS_FUNC_CHECK_SUCCESS;
    uint16_t start_address = *(buffer_rx + 1) | (*(buffer_rx) << 8);
    uint16_t di_count =   *(buffer_rx + 3) | (*(buffer_rx + 2) << 8);
    if(MODBUS_DI_COUNT_MIN <= di_count && di_count <= MODBUS_DI_COUNT_MAX)
    {
        if(start_address >= 0x0000 && ((start_address + di_count) <= 0xFFFF))
        {
            uint16_t byte_count = (uint16_t)((di_count + 7) / 8);
            *(buffer_tx) = byte_count;
            memset((void*)(buffer_tx + 1), 0x00, byte_count);
            *data_size_tx = byte_count + 1;
            printf("MODBUS_FUNC_READ_DI: %04x @ %04x\r\n", di_count, start_address);
        }
        else
        {
            *data_size_tx = 0;
            return_value = MODBUS_FUNC_CHECK_INVALID_AMOUNT;
        }
    }
    else
    {
        *data_size_tx = 0;
        return_value = MODBUS_FUNC_CHECK_INVALID_QUANTITY;
    }
    printf("MODBUS_FUNC_READ_DI: Exit with: %02d\r\n", return_value);
    return return_value;
}

mbFuncCheckRet_t ModBUSFunc_ReadHoldingReg(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx)
{
    mbFuncCheckRet_t return_value = MODBUS_FUNC_CHECK_SUCCESS;
    uint16_t start_address = *(buffer_rx + 1) | (*(buffer_rx) << 8);
    uint16_t hr_count =   *(buffer_rx + 3) | (*(buffer_rx + 2) << 8);
    if(MODBUS_HOLDING_REG_COUNT_MIN <= hr_count && hr_count <= MODBUS_HOLDING_REG_COUNT_MAX)
    {
        if(start_address >= 0x0000 && ((start_address + hr_count) <= 0xFFFF))
        {
            uint16_t byte_count = (uint16_t)(hr_count * 2);
            *(buffer_tx) = byte_count;
            memset((void*)(buffer_tx + 1), 0x00, byte_count);
            *data_size_tx = byte_count + 1;
            printf("MODBUS_FUNC_READ_HOLD_REG: %04x @ %04x\r\n", hr_count, start_address);
        }
        else
        {
            *data_size_tx = 0;
            return_value = MODBUS_FUNC_CHECK_INVALID_AMOUNT;
        }
    }
    else
    {
        *data_size_tx = 0;
        return_value = MODBUS_FUNC_CHECK_INVALID_QUANTITY;
    }
    printf("MODBUS_FUNC_READ_HOLD_REG: Exit with: %02d\r\n");
    return return_value;
}

mbFuncCheckRet_t ModBUSFunc_ReadInputReg(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx)
{
    mbFuncCheckRet_t return_value = MODBUS_FUNC_CHECK_SUCCESS;

    uint16_t start_address = *(buffer_rx + 1) | (*(buffer_rx) << 8);
    uint16_t inreg_count =   *(buffer_rx + 3) | (*(buffer_rx + 2) << 8);
    if(MODBUS_INPUT_REG_COUNT_MIN <= inreg_count && inreg_count <= MODBUS_INPUT_REG_COUNT_MAX)
    {
        if(start_address >= 0x0000 && ((start_address + inreg_count) <= 0xFFFF))
        {
            uint16_t byte_count = (uint16_t)(inreg_count * 2);
            *(buffer_tx) = byte_count;
            memset((void*)(buffer_tx + 1), 0x00, byte_count);
            *data_size_tx = byte_count + 1;
            printf("MODBUS_FUNC_READ_INPUT_REG: %04x @ %04x\r\n", inreg_count, start_address);
        }
        else
        {
            *data_size_tx = 0;
            return_value = MODBUS_FUNC_CHECK_INVALID_AMOUNT;
        }
    }
    else
    {
        *data_size_tx = 0;
        return_value = MODBUS_FUNC_CHECK_INVALID_QUANTITY;
    }
    printf("MODBUS_FUNC_READ_INPUT_REG: Exit with: %02d\r\n");
    return return_value;
}

mbFuncCheckRet_t ModBUSFunc_WriteSingleCoil(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx)
{
    mbFuncCheckRet_t return_value = MODBUS_FUNC_CHECK_SUCCESS;
    uint16_t coil_address = *(buffer_rx + 1) | (*(buffer_rx) << 8);
    uint16_t coil_value =   *(buffer_rx + 3) | (*(buffer_rx + 2) << 8);

    if(coil_address >= 0x0000 && ((coil_address) <= 0xFFFF))
    {
        if (coil_value == 0xFF00 || coil_value == 0x0000)
        {
            memcpy(buffer_tx, buffer_rx, data_size_rx);
            *data_size_tx = data_size_rx;
            printf("MODBUS_FUNC_WRITE_COIL: %s @ %04x\r\n", coil_value == 0x0000 ? "OFF" : "ON", coil_address);
        }
        else
        {
            *data_size_tx = 0;
            return_value = MODBUS_FUNC_CHECK_INVALID_AMOUNT;
        }

    }
    else
    {
        *data_size_tx = 0;
        return_value = MODBUS_FUNC_CHECK_INVALID_QUANTITY;
    }
    printf("MODBUS_FUNC_WRITE_COIL: Exit with: %02d\r\n");
    return return_value;
}

mbFuncCheckRet_t ModBUSFunc_WriteSingleReg(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx)
{
    mbFuncCheckRet_t return_value = MODBUS_FUNC_CHECK_SUCCESS;
    uint16_t hr_address = *(buffer_rx + 1) | (*(buffer_rx) << 8);
    uint16_t hr_value =   *(buffer_rx + 3) | (*(buffer_rx + 2) << 8);

    if(hr_address >= 0x0000 && hr_address <= 0xFFFF)
    {
        if (hr_value >= 0x0000 && hr_value <= 0xFFFF)
        {
            memcpy(buffer_tx, buffer_rx, data_size_rx);
            *data_size_tx = data_size_rx;
            printf("MODBUS_FUNC_WRITE_SINGLE_REG: %04x @ %04x\r\n", hr_value, hr_address);
        }
        else
        {
            *data_size_tx = 0;
            return_value = MODBUS_FUNC_CHECK_INVALID_AMOUNT;
        }

    }
    else
    {
        *data_size_tx = 0;
        return_value = MODBUS_FUNC_CHECK_INVALID_QUANTITY;
    }
    printf("MODBUS_FUNC_WRITE_SINGLE_REG: Exit with: %02d\r\n");
    return return_value;
}

mbFuncCheckRet_t ModBUSFunc_WriteMultiReg(uint8_t* buffer_rx, uint16_t data_size_rx, uint8_t* buffer_tx,  uint16_t* data_size_tx)
{
    mbFuncCheckRet_t return_value = MODBUS_FUNC_CHECK_SUCCESS;
    uint16_t start_address = *(buffer_rx + 1) | (*(buffer_rx) << 8);
    uint16_t hr_count =   *(buffer_rx + 3) | (*(buffer_rx + 2) << 8);

    if(MODBUS_HOLDING_REG_WRITE_COUNT_MIN <= hr_count && hr_count <= MODBUS_HOLDING_REG_WRITE_COUNT_MAX)
    {
        if (start_address >= 0x0000 && ((start_address + hr_count) <= 0xFFFF))
        {
            memcpy(buffer_tx, buffer_rx, MODBUS_HOLDING_REG_WRITE_RESP_SIZE);
            *data_size_tx = MODBUS_HOLDING_REG_WRITE_RESP_SIZE;
            printf("MODBUS_FUNC_WRITE_MULTI_REG: %04x @ %04x\r\n", hr_count, start_address);
        }
        else
        {
            *data_size_tx = 0;
            return_value = MODBUS_FUNC_CHECK_INVALID_AMOUNT;
        }
    }
    else
    {
        *data_size_tx = 0;
        return_value = MODBUS_FUNC_CHECK_INVALID_QUANTITY;
    }
    printf("MODBUS_FUNC_WRITE_MULTI_REG: Exit with: %02d\r\n");
    return return_value;
}