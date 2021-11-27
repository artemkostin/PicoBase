/**
 * @file mb_rpi_mapping.c
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller ModBUS implementation.
 * @version 0.1
 * @date 2021-11-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "mb_rpi_mapping.h"

#define COILS_COUNT 8

static mbPicoGpioDesc_t coils[COILS_COUNT] = {
    {.mode = MODBUS_PICO_GPIO_RESERVED}, //0
    {.mode = MODBUS_PICO_GPIO_RESERVED}, //1
    {.mode = MODBUD_PICO_GPIO_DO},       //2
    {.mode = MODBUD_PICO_GPIO_DO},       //3
    {.mode = MODBUD_PICO_GPIO_DI}, //4
    {.mode = MODBUS_PICO_GPIO_RESERVED}, //5
    {.mode = MODBUS_PICO_GPIO_RESERVED}, //6
    {.mode = MODBUS_PICO_GPIO_RESERVED}  //7

};

bool mbPicoCoils_Write(uint8_t coil, bool state)
{
    for (uint8_t i = 0; i < COILS_COUNT; i++)
    {
        printf("DEBUG: coils[%02d].mode=%02d\r\n", i, coils[i].mode);
        if (i == coil && coils[i].mode == MODBUD_PICO_GPIO_DO)
        {
            gpio_put(i, state);
            printf("DEBUG: Write %02d @ %02d\r\n", state, coil);
            return true;
        }
    }
    printf("DEBUG: Write %02d @ %02d - Ooops\r\n", state, coil);
    return false;
}

uint8_t mbPicoCoils_Read(uint16_t start_coil, uint16_t* amount_left)
{
    uint8_t return_value = 0;
    uint8_t to_return = start_coil + *(amount_left);
    uint8_t bit_count = 0;

    if ((to_return) > COILS_COUNT)
    {
        printf("DEBUG: You want too much: %d of %d\r\n", to_return, COILS_COUNT);
        return return_value;
    }


    for (uint8_t i = start_coil; i < to_return; i++)
    {
        uint8_t bit_value = 0;
        if(coils[i].mode == MODBUD_PICO_GPIO_DO){
            bit_value = gpio_get(i) ? 1 : 0;
        } else {
            bit_value = 0;
        }
        
        printf("DEBUG: OK, read: %02x @ %02x of %02x\r\n", bit_value, i, i);
        return_value |= (bit_value << bit_count++);
        if(bit_count >= 8){
            *(amount_left) -= 8;
            printf("DEBUG: NG, no more space in this byte\r\n");
            break;
        }
    }
    printf("DEBUG: OK, return: %02x\r\n", return_value);
    return return_value;
}

uint8_t mbPicoInputs_Read(uint16_t start_coil, uint16_t* amount_left)
{
    uint8_t return_value = 0;
    uint8_t to_return = start_coil + *(amount_left);
    uint8_t bit_count = 0;

    if ((to_return) > COILS_COUNT)
    {
        printf("DEBUG: You want too much: %d of %d\r\n", to_return, COILS_COUNT);
        return return_value;
    }


    for (uint8_t i = start_coil; i < to_return; i++)
    {
        uint8_t bit_value = 0;
        if(coils[i].mode == MODBUD_PICO_GPIO_DI){
            bit_value = gpio_get(i) ? 1 : 0;
        } else {
            bit_value = 0;
        }
        
        printf("DEBUG: OK, read: %02x @ %02x of %02x\r\n", bit_value, i, i);
        return_value |= (bit_value << bit_count++);
        if(bit_count >= 8){
            *(amount_left) -= 8;
            printf("DEBUG: NG, no more space in this byte\r\n");
            break;
        }
    }
    printf("DEBUG: OK, return: %02x\r\n", return_value);
    return return_value;
}