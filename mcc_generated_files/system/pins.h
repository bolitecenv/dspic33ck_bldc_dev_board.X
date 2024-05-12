/**
 * PINS Generated Driver Header File 
 * 
 * @file      pins.h
 *            
 * @defgroup  pinsdriver Pins Driver
 *            
 * @brief     The Pin Driver directs the operation and function of 
 *            the selected device pins using dsPIC MCUs.
 *
 * @skipline @version   Firmware Driver Version 1.0.2
 *
 * @skipline @version   PLIB Version 1.3.0
 *
 * @skipline  Device : dsPIC33CK256MP508
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H
// Section: Includes
#include <xc.h>

// Section: Device Pin Macros

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC3 GPIO Pin which has a custom name of IO_RC3 to High
 * @pre      The RC3 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define IO_RC3_SetHigh()          (_LATC3 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RC3 GPIO Pin which has a custom name of IO_RC3 to Low
 * @pre      The RC3 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RC3_SetLow()           (_LATC3 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RC3 GPIO Pin which has a custom name of IO_RC3
 * @pre      The RC3 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RC3_Toggle()           (_LATC3 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RC3 GPIO Pin which has a custom name of IO_RC3
 * @param    none
 * @return   none  
 */
#define IO_RC3_GetValue()         _RC3

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC3 GPIO Pin which has a custom name of IO_RC3 as Input
 * @param    none
 * @return   none  
 */
#define IO_RC3_SetDigitalInput()  (_TRISC3 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RC3 GPIO Pin which has a custom name of IO_RC3 as Output
 * @param    none
 * @return   none  
 */
#define IO_RC3_SetDigitalOutput() (_TRISC3 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD10 GPIO Pin which has a custom name of IO_RD10 to High
 * @pre      The RD10 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define IO_RD10_SetHigh()          (_LATD10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD10 GPIO Pin which has a custom name of IO_RD10 to Low
 * @pre      The RD10 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RD10_SetLow()           (_LATD10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD10 GPIO Pin which has a custom name of IO_RD10
 * @pre      The RD10 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RD10_Toggle()           (_LATD10 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD10 GPIO Pin which has a custom name of IO_RD10
 * @param    none
 * @return   none  
 */
#define IO_RD10_GetValue()         _RD10

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD10 GPIO Pin which has a custom name of IO_RD10 as Input
 * @param    none
 * @return   none  
 */
#define IO_RD10_SetDigitalInput()  (_TRISD10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD10 GPIO Pin which has a custom name of IO_RD10 as Output
 * @param    none
 * @return   none  
 */
#define IO_RD10_SetDigitalOutput() (_TRISD10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD11 GPIO Pin which has a custom name of IO_RD11 to High
 * @pre      The RD11 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define IO_RD11_SetHigh()          (_LATD11 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RD11 GPIO Pin which has a custom name of IO_RD11 to Low
 * @pre      The RD11 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RD11_SetLow()           (_LATD11 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RD11 GPIO Pin which has a custom name of IO_RD11
 * @pre      The RD11 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RD11_Toggle()           (_LATD11 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RD11 GPIO Pin which has a custom name of IO_RD11
 * @param    none
 * @return   none  
 */
#define IO_RD11_GetValue()         _RD11

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD11 GPIO Pin which has a custom name of IO_RD11 as Input
 * @param    none
 * @return   none  
 */
#define IO_RD11_SetDigitalInput()  (_TRISD11 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RD11 GPIO Pin which has a custom name of IO_RD11 as Output
 * @param    none
 * @return   none  
 */
#define IO_RD11_SetDigitalOutput() (_TRISD11 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE4 GPIO Pin which has a custom name of IO_RE4 to High
 * @pre      The RE4 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define IO_RE4_SetHigh()          (_LATE4 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE4 GPIO Pin which has a custom name of IO_RE4 to Low
 * @pre      The RE4 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RE4_SetLow()           (_LATE4 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RE4 GPIO Pin which has a custom name of IO_RE4
 * @pre      The RE4 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RE4_Toggle()           (_LATE4 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RE4 GPIO Pin which has a custom name of IO_RE4
 * @param    none
 * @return   none  
 */
#define IO_RE4_GetValue()         _RE4

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE4 GPIO Pin which has a custom name of IO_RE4 as Input
 * @param    none
 * @return   none  
 */
#define IO_RE4_SetDigitalInput()  (_TRISE4 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE4 GPIO Pin which has a custom name of IO_RE4 as Output
 * @param    none
 * @return   none  
 */
#define IO_RE4_SetDigitalOutput() (_TRISE4 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE10 GPIO Pin which has a custom name of IO_RE10 to High
 * @pre      The RE10 must be set as Output Pin             
 * @param    none
 * @return   none  
 */
#define IO_RE10_SetHigh()          (_LATE10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Sets the RE10 GPIO Pin which has a custom name of IO_RE10 to Low
 * @pre      The RE10 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RE10_SetLow()           (_LATE10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Toggles the RE10 GPIO Pin which has a custom name of IO_RE10
 * @pre      The RE10 must be set as Output Pin
 * @param    none
 * @return   none  
 */
#define IO_RE10_Toggle()           (_LATE10 ^= 1)

/**
 * @ingroup  pinsdriver
 * @brief    Reads the value of the RE10 GPIO Pin which has a custom name of IO_RE10
 * @param    none
 * @return   none  
 */
#define IO_RE10_GetValue()         _RE10

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE10 GPIO Pin which has a custom name of IO_RE10 as Input
 * @param    none
 * @return   none  
 */
#define IO_RE10_SetDigitalInput()  (_TRISE10 = 1)

/**
 * @ingroup  pinsdriver
 * @brief    Configures the RE10 GPIO Pin which has a custom name of IO_RE10 as Output
 * @param    none
 * @return   none  
 */
#define IO_RE10_SetDigitalOutput() (_TRISE10 = 0)

/**
 * @ingroup  pinsdriver
 * @brief    Initializes the PINS module
 * @param    none
 * @return   none  
 */
void PINS_Initialize(void);

/**
 * @ingroup  pinsdriver
 * @brief    This function is callback for IO_RC3 Pin
 * @param    none
 * @return   none   
 */
void IO_RC3_CallBack(void);

/**
 * @ingroup  pinsdriver
 * @brief    This function is callback for IO_RD10 Pin
 * @param    none
 * @return   none   
 */
void IO_RD10_CallBack(void);

/**
 * @ingroup  pinsdriver
 * @brief    This function is callback for IO_RD11 Pin
 * @param    none
 * @return   none   
 */
void IO_RD11_CallBack(void);


/**
 * @ingroup    pinsdriver
 * @brief      This function assigns a function pointer with a callback address
 * @param[in]  InterruptHandler - Address of the callback function 
 * @return     none  
 */
void IO_RC3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup    pinsdriver
 * @brief      This function assigns a function pointer with a callback address
 * @param[in]  InterruptHandler - Address of the callback function 
 * @return     none  
 */
void IO_RD10_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup    pinsdriver
 * @brief      This function assigns a function pointer with a callback address
 * @param[in]  InterruptHandler - Address of the callback function 
 * @return     none  
 */
void IO_RD11_SetInterruptHandler(void (* InterruptHandler)(void));


#endif
