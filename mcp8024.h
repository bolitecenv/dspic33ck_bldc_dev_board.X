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
#ifndef MCP8024_H
#define	MCP8024_H

#include <xc.h> // include processor files - each processor file is guarded.  



// 8bit 1: host->mcp ,  0: mcp->host
// 7bit 1: ack,         0:nack


// HOST --> MCP8024
#define     MCP8024_SET_CFG_0   0x81
#define     MCP8024_SET_CFG_1   0x83
#define     MCP8024_SET_CFG_2   0x87
#define     MCP8024_GET_CFG_0   0x82
#define     MCP8024_GET_CFG_1   0x84
#define     MCP8024_GET_CFG_2   0x88
#define     MCP8024_STATUS_0   0x85
#define     MCP8024_STATUS_1   0x86


// MCP8024 --> HOST


// MASK
#define     MCP8024_Normal_OP                       0x00
#define     MCP8024_TempWarning                     0x01
#define     MCP8024_OverTemp                        0x02
#define     MCP8024_UnderVoltage                    0x04
#define     MCP8024_OverVoltage                     0x10
#define     MCP8024_BR_OverCurrent                  0x20
#define     MCP8024_BR_OutputUnderVoltageWarning    0x40
#define     MCP8024_BR_OutputUnderVoltage           0x80




#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

