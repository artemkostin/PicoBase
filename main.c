/**
 * @file main.c
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller entry point.
 * @version 0.1
 * @date 2021-09-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "heartbeat.h"
#include "cli.h"
#include "mb_node.h"

/**
 * @brief Initialize all required HW and SW modules.
 *
 */
void bsp_init(void){
    stdio_init_all();
    UtHeartBeat_Init(500);
    UtCli_Init();
    AppModBUS_Init(1);
}

/**
 * @brief programm entry point
 *
 * @return 0, which is never reached
 */
int main()
{
    bsp_init();
    while(1){
        UtHeartBeat_Run();
        UtCli_Run();
        AppModBUS_Run();
    }

    return 0;
}
