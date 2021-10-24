/**
 * @file mb_crc.h
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller ModBUS implementation.
 * @version 0.1
 * @date 2021-09-25
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef SGP_APPS_MODBUS_CRC
#define SGP_APPS_MODBUS_CRC

#include <stdint.h>

uint16_t CRC16t (uint8_t* puchMsg, uint16_t usDataLen);
uint16_t CRC16r (uint8_t* buf, uint16_t len);

#endif //SGP_APPS_MODBUS_CRC