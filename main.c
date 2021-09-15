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

/**
 * @brief Initialize all required HW and SW modules.
 *
 */
void bsp_init(void){
    stdio_init_all();
}

/**
 * @brief programm entry point
 *
 * @return 0, which is never reached
 */
int main()
{
    bsp_init();

    puts("Hello, world!");

    //Mainloop
    while(1){
    ;
    }

    return 0;
}
