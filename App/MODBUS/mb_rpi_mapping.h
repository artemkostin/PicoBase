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
#include "pico/stdlib.h"

typedef enum
{
    MODBUD_PICO_GPIO_DI = 0,
    MODBUD_PICO_GPIO_DO,
    MODBUD_PICO_GPIO_AI,
    MODBUD_PICO_GPIO_AO,
    MODBUD_PICO_GPIO_TOTAL
} mbPicoGpioMode_t;

typedef struct
{
    uint8_t position;
    bool is_enabled;
    mbPicoGpioMode_t mode;
} mbPicoGpioDesc_t;

bool mbPicoCoils_Write(uint8_t coil, bool state);
bool mbPicoCoils_Read(uint8_t coil, bool state);

#endif