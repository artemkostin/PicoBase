/**
 * @file cli.h
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller CLI interface.
 * @version 0.1
 * @date 2021-09-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SGP_APPS_CLI
#define SGP_APPS_CLI
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/watchdog.h"
#include "devinfo.h"

#define COMMAND_BUFFER_MAX_SIZE 256
#define COMMAND_MAX_SIZE 32

typedef enum {
    CLI_RESULT_SUCESS = 0x00,
    CLI_RESULT_FAIL,
    CLI_RESULT_TOTAL
}utcli_result_t;

typedef enum {
    CLI_AT_UNKNOWN = 0x0000,
    CLI_AT_REBOOT,
    CLI_AT_INFO,
    CLI_AT_PARAMS_SET,
    CLI_AT_PARAMS_GET,
    CLI_AT_MODBUS,
    CLI_AT_AUTH,
    CLI_AT_TOTAL
} utcli_cmd_id_t;

typedef struct
{
    utcli_cmd_id_t id;
    const char* name;
    const char* description;
}utcli_cmd_description_t;

typedef utcli_result_t (*handler_function)(char* buffer, uint16_t len);

void UtCli_Init(void);
void UtCli_Run(void);
utcli_cmd_id_t UtCli_ParseInput(char* buffer, int len);
utcli_result_t UtCli_CallHandler(utcli_cmd_id_t handler_id, char* buffer, int len);

#endif //SGP_APPS_CLI