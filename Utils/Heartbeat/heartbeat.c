/**
 * @file heartbeat.c
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller heartbeat interface.
 * @version 0.1
 * @date 2021-09-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "heartbeat.h"

static uint32_t hb_period;
static const uint LED_PIN = HEARTBEAT_LED;

static void UtHeartBeat_UpdateState(bool* currentState) {
    if (*currentState)
    {
        *currentState = false;
    }
    else
    {
        *currentState = true;
    }
    gpio_put(LED_PIN, (int)(*currentState));
}

void UtHeartBeat_Init(uint32_t period)
{
    UtHeartBeat_SetPeriod(period);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // puts("UtHeartBeat_SetPeriod");
};

void UtHeartBeat_Run()
{
    static bool is_enable = false;
    static uint32_t last_run = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());

    if((now - last_run) > hb_period) {
        UtHeartBeat_UpdateState(&is_enable);
        last_run = now;
    }
};

void UtHeartBeat_SetPeriod(uint32_t period)
{
    hb_period = period;
};

uint32_t UtHeartBeat_GetPeriod(void)
{
    return hb_period;
};