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

static mbPicoGpioDesc_t coils[] = {
    { .position = 2, .is_enabled = false, .mode = MODBUD_PICO_GPIO_DO },
    { .position = 3, .is_enabled = false, .mode = MODBUD_PICO_GPIO_DO }
};

bool mbPicoCoils_Write(uint8_t coil, bool state)
{
    for(uint8_t i = 0; i < (sizeof(coils)/sizeof(mbPicoGpioDesc_t)); i++) {
        if(i == coil) {
            gpio_put(coils[i].position, state);
            return true;
        }
    }
    return false;
}

bool mbPicoCoils_Read(uint8_t coil, bool state)
{
    for(uint8_t i = 0; i < (sizeof(coils)/sizeof(mbPicoGpioDesc_t)); i++) {
        if(i == coil) {
            return gpio_get(coils[i].position);
        }
    }
    return false;
}