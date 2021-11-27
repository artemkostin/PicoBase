/**
 * @file mb_rpi_mapping.h
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller ModBUS implementation.
 * @version 0.1
 * @date 2021-01-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef SGP_APPS_MB_RPI_MAPPING_H
#define SGP_APPS_MB_RPI_MAPPING_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "pico/stdlib.h"

typedef enum
{
    MODBUS_PICO_GPIO_RESERVED = 0,
    MODBUD_PICO_GPIO_DI,
    MODBUD_PICO_GPIO_DO,
    MODBUD_PICO_GPIO_AI,
    MODBUD_PICO_GPIO_AO,
    MODBUD_PICO_GPIO_TOTAL
}mbPicoGpioMode_t;

typedef struct
{
    mbPicoGpioMode_t mode;
} mbPicoGpioDesc_t;

bool mbPicoCoils_Write(uint8_t coil, bool state);
uint8_t mbPicoCoils_Read(uint16_t start_coil, uint16_t* amount_left);

#endif