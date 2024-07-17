/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DATA_SENDER_H
#define	DATA_SENDER_H

#include <xc.h> // include processor files - each processor file is guarded.  




#define HEADER_CODE     0x80 // This is magic number.

#define TYPE_COMMAND    0x01
#define TYPE_DATA       0x02
#define TYPE_LOG        0x03


typedef struct{
    uint8_t     type;
    uint8_t     mcp_state;
    uint16_t    length;
}__attribute__((__packed__)) StaticHeader_ST;

typedef struct{
    uint16_t     data_length;
    uint8_t*     data;
}__attribute__((__packed__)) Data_ST;

typedef struct{
    StaticHeader_ST*    header;
    Data_ST*            payload;
}__attribute__((__packed__)) Message_ST;




void static_header();
void Send_Data(uint8_t mcp_state, uint8_t type, uint8_t* data, uint16_t length);
void Send_Command(uint8_t mcp_state);



#endif	/* XC_HEADER_TEMPLATE_H */

