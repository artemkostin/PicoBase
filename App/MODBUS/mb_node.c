/**
 * @file mb_node.c
 * @author Artem Kostin (artem.1.kostin@gmail.com)
 * @brief SmartGardenProject pot controller ModBUS implementation.
 * @version 0.1
 * @date 2021-09-26
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "mb_node.h"

static uint8_t modbusRxBuffer[MODBUS_BUFFER_SIZE] = {0};
static uint8_t modbusTxBuffer[MODBUS_BUFFER_SIZE] = {0};
static uint8_t node_address = MODBUS_DEFAULT_INVALID_ADDRESS;
static mbADUFrame_t frame = {0};

static inline void printTx(uint16_t len){
    printf("TX: To send:%d, Buffer: ", len);
    for(int i = 0; i < len; i++){
        printf("%02x ", modbusTxBuffer[i]);
    }
    printf("\r\n");
}

static inline void printRx(uint16_t len){
    printf("RX: Received:%d, Buffer: ", len);
    for(int i = 0; i < len; i++){
        printf("%02x ", modbusRxBuffer[i]);
    }
    printf("\r\n");
}
static inline void mb_adu_frame_reset(void)
{
    frame.address = 0;
    frame.crc = 0;
    frame.data = 0;
    frame.data_size = 0;
    frame.func_code = 0;
}
static mbADUResults_t mb_process_adu(uint8_t* buffer, uint16_t len)
{
    uint16_t frameCrcCalculated = 0;
    mbADUResults_t return_value = MODBUS_ADU_TOTAL;
    mb_adu_frame_reset();

    printf("Received: %d bytes\r\n", len);
    do {
        if(len < MODBUS_FRAME_MIN_LENGHT)
        {
            return_value = MODBUS_ADU_WRONG_FRAME;
            break;
        }

        frame.address = *(buffer + MODBUS_FRAME_ADDRESS_OFFSET);
        frame.func_code = *(buffer + MODBUS_FRAME_FUNCCODE_OFFSET);
        frame.crc = *(buffer + (len - 2)) | (*(buffer + (len - 1)) << 8);
        frameCrcCalculated = CRC16t(buffer, (len - MODBUS_FRAME_CRC_SIZE));
        if(len > MODBUS_FRAME_MIN_LENGHT)
        {
            frame.data = (uint8_t*)(buffer + MODBUS_FRAME_DATA_OFFSET);
            frame.data_size = (uint16_t)(len - (MODBUS_FRAME_DATA_OFFSET + MODBUS_FRAME_CRC_SIZE));
        }

        if(frame.address != 0 && frame.address != node_address)
        {
            return_value = MODBUS_ADU_MISMATCH_ADDRESS;
            break;
        }

        if(frame.crc != frameCrcCalculated)
        {
            return_value = MODBUS_ADU_MISMATCH_CRC;
            break;
        }

        return_value = MODBUS_ADU_SUCCESS;
    }while (0);

    printf("To: %02x, func: %02x\r\n", frame.address, frame.func_code);
    printf("CRC: frame: %04x, real: %04x\r\n", frame.crc, frameCrcCalculated);
    printf("Data: %08x\r\n", frame.data);
    printf("Done with: %02d\r\n", return_value);
    return return_value;
}

static mbPDUResults_t mb_process_pdu(uint8_t func, uint8_t* data, uint16_t data_size_rx, uint8_t* data_tx, uint16_t* data_size_tx)
{
    mbPDUResults_t return_value = MODBUS_PDU_TOTAL;
    switch (func)
    {
        case MODBUS_FUNC_READ_COILS:
        {
            return_value = ModBUSFunc_ReadCoils(data, data_size_rx, data_tx, data_size_tx);
            break;
        }
        case MODBUS_FUNC_READ_DI:
        {
            return_value = ModBUSFunc_ReadDiscreteInput(data, data_size_rx, data_tx, data_size_tx);
            break;
        }
        case MODBUS_FUNC_READ_HOLD_REG:
        {
            return_value = ModBUSFunc_ReadHoldingReg(data, data_size_rx, data_tx, data_size_tx);
            break;
        }
        case MODBUS_FUNC_READ_INPUT_REG:
        {
            return_value = ModBUSFunc_ReadInputReg(data, data_size_rx, data_tx, data_size_tx);
            break;
        }
        case MODBUS_FUNC_WRITE_SINGLE_COIL:
        {
            return_value = ModBUSFunc_WriteSingleCoil(data, data_size_rx, data_tx, data_size_tx);
            break;
        }
        case MODBUS_FUNC_WRITE_SINGLE_REG:
        {
            return_value = ModBUSFunc_WriteSingleReg(data, data_size_rx, data_tx, data_size_tx);
            break;
        }
        case MODBUS_FUNC_WRITE_MULTI_REG:
        {
            return_value = ModBUSFunc_WriteMultiReg(data, data_size_rx, data_tx, data_size_tx);
            break;
        }
        default:
        {
            printf("Unsupported func: %d\r\n", func);
            return_value = MODBUS_PDU_ILLIGAL_FUNC;
            break;
        }
    }
    return return_value;
}

void AppModBUS_Init(uint8_t address)
{
    // Initialise UART 0
    uart_init(MODBUS_UART_INTERFACE, MODBUS_UART_SPEED);
    uart_set_format(MODBUS_UART_INTERFACE, 8, 1, UART_PARITY_NONE);
    // Set the GPIO pin mux to the UART - 0 is TX, 1 is RX
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    //Todo: FIX initialization
    gpio_init(2);
    gpio_set_dir(2, GPIO_OUT);
    gpio_put(2, false);
    gpio_set_drive_strength(2, GPIO_DRIVE_STRENGTH_12MA);

    gpio_init(3);
    gpio_set_dir(3, GPIO_OUT);
    gpio_put(3, false);
    gpio_set_drive_strength(3, GPIO_DRIVE_STRENGTH_12MA);

    gpio_init(4);
    gpio_set_dir(4, GPIO_IN);
    node_address = address;
};

void AppModBUS_Run(void)
{
    static mbNodeStates_t mbState = MODBUS_STATE_IDLE;
    static uint16_t bufferPointer = 0;
    static mbADUResults_t aduRetCode = MODBUS_ADU_TOTAL;
    static mbPDUResults_t pduRetCode = MODBUS_PDU_TOTAL;

    mbNodeStates_t nextState = MODBUS_STATE_IDLE;

    switch (mbState)
    {
        case MODBUS_STATE_IDLE:
        {
            nextState = MODBUS_STATE_IDLE;
            if(uart_is_readable_within_us(MODBUS_UART_INTERFACE, MODBUS_UART_TIMEOUT_US)){
                modbusRxBuffer[bufferPointer++] = uart_getc(MODBUS_UART_INTERFACE);
            } else {
                if(bufferPointer > 0) {
                    aduRetCode = MODBUS_ADU_TOTAL;
                    pduRetCode = MODBUS_PDU_TOTAL;
                    nextState = MODBUS_STATE_REQUEST_CHECK;
                }
            }
            break;
        }
        case MODBUS_STATE_REQUEST_CHECK:
        {
            //try to proceed
            printRx(bufferPointer);
            aduRetCode = mb_process_adu(modbusRxBuffer, bufferPointer);
            if(aduRetCode > MODBUS_ADU_SUCCESS)
            {
                nextState = MODBUS_STATE_IDLE;
                bufferPointer = 0;
            }
            else
            {
                nextState = MODBUS_STATE_REQUEST_PROCESS;
            }
            break;
        }
        case MODBUS_STATE_REQUEST_PROCESS:
        {
            bufferPointer = MODBUS_BUFFER_SIZE - MODBUS_RESPONSE_BUFFER_REDUCTION;
            pduRetCode = mb_process_pdu(frame.func_code, frame.data, frame.data_size,
                        (uint8_t*)(modbusTxBuffer + MODBUS_FRAME_DATA_OFFSET), &bufferPointer);
            if(pduRetCode > MODBUS_PDU_SUCCESS)
            {
                nextState = MODBUS_STATE_REPLY_ERROR;
                puts("Reply error");
            }
            else
            {
                nextState = MODBUS_STATE_REPLY_NORMAL;
                puts("Reply normal");
            }
            break;
        }
        case MODBUS_STATE_REPLY_NORMAL:
        {
            uint16_t crc = 0;
            if(frame.address == 0) {
                puts("No reply to broadcast message");
                nextState = MODBUS_STATE_IDLE;
                break;
            }
            modbusTxBuffer[MODBUS_FRAME_ADDRESS_OFFSET] = frame.address;
            modbusTxBuffer[MODBUS_FRAME_FUNCCODE_OFFSET] = frame.func_code;
            bufferPointer += MODBUS_FRAME_DATA_OFFSET;
            crc = CRC16t(modbusTxBuffer, bufferPointer);
            modbusTxBuffer[bufferPointer++] = (crc & 0x00FF);
            modbusTxBuffer[bufferPointer++] = ((crc & 0xFF00) >> 8);
            nextState = MODBUS_STATE_RESPONCE_SENDING;
            break;
        }
        case MODBUS_STATE_REPLY_ERROR:
        {
            uint16_t crc = 0;
            modbusTxBuffer[MODBUS_FRAME_ADDRESS_OFFSET] = frame.address;
            modbusTxBuffer[MODBUS_FRAME_FUNCCODE_OFFSET] = frame.func_code + MODBUS_ERROR_RESPONSE_CODE_OFFSET;
            modbusTxBuffer[MODBUS_FRAME_DATA_OFFSET] = (uint8_t)pduRetCode;
            bufferPointer += (MODBUS_FRAME_DATA_OFFSET + 1);
            crc = CRC16t(modbusTxBuffer, bufferPointer);
            modbusTxBuffer[bufferPointer++] = (crc & 0x00FF);
            modbusTxBuffer[bufferPointer++] = ((crc & 0xFF00) >> 8);
            nextState = MODBUS_STATE_RESPONCE_SENDING;
            break;
        }
        case MODBUS_STATE_RESPONCE_SENDING:
        {
            printTx(bufferPointer);
            uart_write_blocking(MODBUS_UART_INTERFACE, modbusTxBuffer, bufferPointer);
            bufferPointer = 0;
            nextState = MODBUS_STATE_IDLE;
            break;
        }
        default:
        {
            break;
        }
    }
    mbState = nextState;
};

void AppModBUS_SetAddress(uint8_t address)
{
    node_address = address;
};
