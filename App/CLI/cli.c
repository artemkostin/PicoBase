/**
 * @file cli.c
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller CLI implementation.
 * @version 0.1
 * @date 2021-09-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "cli.h"

static char command_buffer[COMMAND_BUFFER_MAX_SIZE] = {0};
static const utcli_cmd_description_t cmd_desc[CLI_AT_TOTAL] = {
    {.id = CLI_AT_UNKNOWN,    .name = "help",   .description = "Show this text"},
    {.id = CLI_AT_REBOOT,     .name = "reboot", .description = "Restart the board"},
    {.id = CLI_AT_BOOTLOADER, .name = "boot",   .description = "Reboot to usb bootloader"},
    {.id = CLI_AT_INFO,       .name = "info",   .description = "Show device info"},
    {.id = CLI_AT_PARAMS_SET, .name = "set",    .description = "Set DB parameter"},
    {.id = CLI_AT_PARAMS_GET, .name = "get",    .description = "Get DB parameter"},
    {.id = CLI_AT_MODBUS,     .name = "modbus", .description = "Go to ModBus"},
    {.id = CLI_AT_AUTH,       .name = "auth",   .description = "Authentificate me"}
};

static utcli_result_t cli_at_help_handler(char* buffer, uint16_t len)
{
    for(int i = CLI_AT_UNKNOWN; i < CLI_AT_TOTAL; i++){
        printf("Id: %04d, Cmd: %10s, Descr: %s\n", cmd_desc[i].id, cmd_desc[i].name, cmd_desc[i].description);
    }
    return CLI_RESULT_SUCESS;
}

static utcli_result_t cli_at_reboot_handler(char* buffer, uint16_t len)
{
    watchdog_enable(500, 0);
    printf("Waiting to be rebooted by watchdog\n");
    return CLI_RESULT_SUCESS;
}
static utcli_result_t cli_at_bootloader_handler(char* buffer, uint16_t len)
{
    reset_usb_boot((1 << PICO_DEFAULT_LED_PIN), 0);
    printf("Reboot to usb bootloader\n");
    sleep_ms(500);
    return CLI_RESULT_SUCESS;
}
static utcli_result_t cli_at_info_handler(char* buffer, uint16_t len)
{
    const devinfo_t* di = UtDevInfo_GetInfo();
    printf("%d.%d.%d of %s - %s at %d\r\n",
        di->version_major,
        di->version_minor,
        di->version_revision,
        di->project,
        di->role,
        di->address);
    return CLI_RESULT_SUCESS;
}
static utcli_result_t cli_at_param_set_handler(char* buffer, uint16_t len)
{
    puts("CLI: AT: Params SET");
    return CLI_RESULT_FAIL;
}
static utcli_result_t cli_at_param_get_handler(char* buffer, uint16_t len)
{
    puts("CLI: AT: Params GET");
    return CLI_RESULT_FAIL;
}
static utcli_result_t cli_at_modbus_handler(char* buffer, uint16_t len)
{
    puts("CLI: AT: Modbus");
    return CLI_RESULT_FAIL;
}
static utcli_result_t cli_at_auth_handler(char* buffer, uint16_t len)
{
    puts("CLI: AT: Auth");
    return CLI_RESULT_FAIL;
}


static handler_function cli_callbacks[CLI_AT_TOTAL] = {
    &cli_at_help_handler,
    &cli_at_reboot_handler,
    &cli_at_bootloader_handler,
    &cli_at_info_handler,
    &cli_at_param_set_handler,
    &cli_at_param_get_handler,
    &cli_at_modbus_handler,
    &cli_at_auth_handler
};

static int get_input() {
    int ch = 0, pos = 0;
    do {
        ch = getchar_timeout_us(0);
        if(ch > 0)
        {
            if(pos < (COMMAND_BUFFER_MAX_SIZE - 1))
            {
                command_buffer[pos++] = (char)ch;
            }
            else
            {
                pos = -1;
                break;
            }
        }
    } while (ch > 0);
    return pos;
};

void UtCli_Init(void)
{
    puts("hello cli");
};

void UtCli_Run(void)
{
    static int position = 0;
    position = get_input();

    if (position <= 0) { return; }

    utcli_cmd_id_t res = UtCli_ParseInput(command_buffer, position);
    utcli_result_t cmd_res = UtCli_CallHandler(res, command_buffer, position);
    printf("%s@%s\r\n", cmd_res ? "NG" : "OK", cmd_desc[res].name);
    position = 0;
};

utcli_cmd_id_t UtCli_ParseInput(char* buffer, int len)
{
    utcli_cmd_id_t returnValue = CLI_AT_UNKNOWN;
    if(buffer[0] == '!' && (buffer[len - 1] == '\r' ||  buffer[len - 2] == '\r')){
        char command[COMMAND_MAX_SIZE] = {0};
        sscanf(buffer, "!%s\r", &command);
        for(int i = 0; i < CLI_AT_TOTAL; i++){
            if(!strncmp((command), cmd_desc[i].name, strlen(command)))
            {
                returnValue = cmd_desc[i].id;
                break;
            }
        }
    }
    return returnValue;
};

utcli_result_t UtCli_CallHandler(utcli_cmd_id_t handler_id, char* buffer, int len){
    return cli_callbacks[handler_id] != 0 ? cli_callbacks[handler_id](buffer, 0) : CLI_RESULT_FAIL;
};