/*
 * File:   data_sender.c
 * Author: Bolitec
 *
 * Created on 2024/07/14, 21:01
 */

#include "main.h"
#include "data_sender.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void UART_Write_Message(const void *buf, size_t count)
{
    int bytes_written = 0;
    int result = 0;
    uint8_t *cp;
    
    cp = (uint8_t *)buf;

    while (bytes_written < count)
    {
        UART2_Write(*(cp+bytes_written));

        bytes_written += 1;
    }
}

void Send_Data(uint8_t mcp_state, uint8_t type, uint8_t* data, uint16_t length)
{
    Message_ST message;
    uint16_t message_length;
   
    
    StaticHeader_ST static_header;
    static_header.type = HEADER_CODE | type;
    static_header.mcp_state = mcp_state;
    
    message.header = &static_header;
    Data_ST payload;
    payload.data = data;
    payload.data_length = length;
    
    message.payload = &payload;
    
    message_length = sizeof(StaticHeader_ST) + sizeof(Data_ST) + length;
    message.header->length = message_length;
    message.payload->data_length = length;
    
    UART_Write_Message(message.header, sizeof(StaticHeader_ST));
    UART_Write_Message(message.payload->data, message.payload->data_length);
}

void Send_Command(uint8_t mcp_state)
{
    Message_ST message;

    StaticHeader_ST static_header;
    static_header.type = HEADER_CODE | TYPE_COMMAND;
    static_header.mcp_state = mcp_state;
    
    message.header = &static_header;
    
    message.header->length = sizeof(StaticHeader_ST);
    
    UART_Write_Message(message.header, message.header->length);
}