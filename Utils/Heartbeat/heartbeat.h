/**
 * @file heartbeat.h
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller heartbeat interface.
 * @version 0.1
 * @date 2021-09-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SGP_UTILS_HEARTBEAT
#define SGP_UTILS_HEARTBEAT
#include <stdint.h>
#include "pico/stdlib.h"


#define USE_ON_BOARD_DEFAULT_LED

#ifdef USE_ON_BOARD_DEFAULT_LED
    #ifndef PICO_DEFAULT_LED_PIN
        #error regular LED is required.
    #endif
    #define HEARTBEAT_LED PICO_DEFAULT_LED_PIN
#else
    #error LED pin is not defined. Please define HEARTBEAT_LED.
#endif

void UtHeartBeat_Init(uint32_t period);
void UtHeartBeat_Run();
void UtHeartBeat_SetPeriod(uint32_t period);
uint32_t UtHeartBeat_GetPeriod(void);

#endif //SGP_UTILS_HEARTBEAT
