/**
 * PINS Generated Driver Source File 
 * 
 * @file      pins.c
 *            
 * @ingroup   pinsdriver
 *            
 * @brief     This is the generated driver source file for PINS driver.
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

// Section: Includes
#include <xc.h>
#include <stddef.h>
#include "../pins.h"

// Section: File specific functions
static void (*IO_RC3_InterruptHandler)(void) = NULL;
static void (*IO_RD10_InterruptHandler)(void) = NULL;
static void (*IO_RD11_InterruptHandler)(void) = NULL;

// Section: Driver Interface Function Definitions
void PINS_Initialize(void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;
    LATC = 0x1800;
    LATD = 0x0000;
    LATE = 0x0010;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x000E;
    TRISB = 0x03F9;
    TRISC = 0xE7FF;
    TRISD = 0xFFFC;
    TRISE = 0xFBEF;


    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPUA = 0x0000;
    CNPUB = 0x0000;
    CNPUC = 0x1000;
    CNPUD = 0x0000;
    CNPUE = 0x0000;
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPDC = 0x0000;
    CNPDD = 0x0000;
    CNPDE = 0x0000;


    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x1000;
    ODCD = 0x0000;
    ODCE = 0x0000;


    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x001F;
    ANSELB = 0x009C;
    ANSELC = 0x00C7;
    ANSELD = 0x2000;
    ANSELE = 0x000F;

    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
     __builtin_write_RPCON(0x0000); // unlock PPS

        RPINR18bits.U1RXR = 0x003D; //RC13->UART1:U1RX;
        RPINR19bits.U2RXR = 0x003A; //RC10->UART2:U2RX;
        RPOR14bits.RP60R = 0x0001;  //RC12->UART1:U1TX;
        RPOR13bits.RP59R = 0x0003;  //RC11->UART2:U2TX;

     __builtin_write_RPCON(0x0800); // lock PPS

    /*******************************************************************************
    * Interrupt On Change: any
    *******************************************************************************/
    CNEN0Cbits.CNEN0C3 = 1; //Pin : RC3; 
    CNEN1Cbits.CNEN1C3 = 1; //Pin : RC3; 
    /*******************************************************************************
    * Interrupt On Change: any
    *******************************************************************************/
    CNEN0Dbits.CNEN0D10 = 1; //Pin : RD10; 
    CNEN1Dbits.CNEN1D10 = 1; //Pin : RD10; 
    /*******************************************************************************
    * Interrupt On Change: any
    *******************************************************************************/
    CNEN0Dbits.CNEN0D11 = 1; //Pin : RD11; 
    CNEN1Dbits.CNEN1D11 = 1; //Pin : RD11; 

    /****************************************************************************
     * Interrupt On Change: flag
     ***************************************************************************/
    CNFCbits.CNFC3 = 0;    //Pin : IO_RC3
    CNFDbits.CNFD10 = 0;    //Pin : IO_RD10
    CNFDbits.CNFD11 = 0;    //Pin : IO_RD11

    /****************************************************************************
     * Interrupt On Change: config
     ***************************************************************************/
    CNCONCbits.CNSTYLE = 1; //Config for PORTC
    CNCONCbits.ON = 1; //Config for PORTC
    CNCONDbits.CNSTYLE = 1; //Config for PORTD
    CNCONDbits.ON = 1; //Config for PORTD

    /* Initialize IOC Interrupt Handler*/
    IO_RC3_SetInterruptHandler(&IO_RC3_CallBack);
    IO_RD10_SetInterruptHandler(&IO_RD10_CallBack);
    IO_RD11_SetInterruptHandler(&IO_RD11_CallBack);

    /****************************************************************************
     * Interrupt On Change: Interrupt Enable
     ***************************************************************************/
    IFS1bits.CNCIF = 0; //Clear CNCI interrupt flag
    IEC1bits.CNCIE = 1; //Enable CNCI interrupt
    IFS4bits.CNDIF = 0; //Clear CNDI interrupt flag
    IEC4bits.CNDIE = 1; //Enable CNDI interrupt
}

void __attribute__ ((weak)) IO_RC3_CallBack(void)
{

}

void __attribute__ ((weak)) IO_RD10_CallBack(void)
{

}

void __attribute__ ((weak)) IO_RD11_CallBack(void)
{

}

void IO_RC3_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC1bits.CNCIE = 0; //Disable CNCI interrupt
    IO_RC3_InterruptHandler = InterruptHandler; 
    IEC1bits.CNCIE = 1; //Enable CNCI interrupt
}

void IO_RD10_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC4bits.CNDIE = 0; //Disable CNDI interrupt
    IO_RD10_InterruptHandler = InterruptHandler; 
    IEC4bits.CNDIE = 1; //Enable CNDI interrupt
}

void IO_RD11_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC4bits.CNDIE = 0; //Disable CNDI interrupt
    IO_RD11_InterruptHandler = InterruptHandler; 
    IEC4bits.CNDIE = 1; //Enable CNDI interrupt
}

/* Interrupt service function for the CNCI interrupt. */
void __attribute__ (( interrupt, no_auto_psv )) _CNCInterrupt (void)
{
    if(CNFCbits.CNFC3 == 1)
    {
        if(IO_RC3_InterruptHandler != NULL) 
        { 
            IO_RC3_InterruptHandler(); 
        }
        
        CNFCbits.CNFC3 = 0;  //Clear flag for Pin - IO_RC3
    }
    
    // Clear the flag
    IFS1bits.CNCIF = 0;
}

/* Interrupt service function for the CNDI interrupt. */
void __attribute__ (( interrupt, no_auto_psv )) _CNDInterrupt (void)
{
    if(CNFDbits.CNFD10 == 1)
    {
        if(IO_RD10_InterruptHandler != NULL) 
        { 
            IO_RD10_InterruptHandler(); 
        }
        
        CNFDbits.CNFD10 = 0;  //Clear flag for Pin - IO_RD10
    }
    
    if(CNFDbits.CNFD11 == 1)
    {
        if(IO_RD11_InterruptHandler != NULL) 
        { 
            IO_RD11_InterruptHandler(); 
        }
        
        CNFDbits.CNFD11 = 0;  //Clear flag for Pin - IO_RD11
    }
    
    // Clear the flag
    IFS4bits.CNDIF = 0;
}

