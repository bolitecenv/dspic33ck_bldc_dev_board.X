/*
? [2024] Microchip Technology Inc. and its subsidiaries.

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

#include <stdbool.h>

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/adc/adc1.h"
#include "mcc_generated_files/pwm_hs/pwm.h"
#include "mcc_generated_files/pwm_hs/pwm_hs_interface.h"


/*
    Main application
*/

uint8_t sine_wave[] = {127,121,112,100,88,76,64,52,40,28,16,4,0,4,16,28,40,52,64,76,88,100,112,121};
uint8_t fault_flag = 0;

volatile uint8_t COMPA_flag, COMPB_flag, COMPC_flag;

volatile uint8_t Motor_Power = 30;

uint16_t Get_Duty(uint8_t duty)
{
    return (uint16_t)(PG1PER/100*duty);
}

uint8_t Get_Power(uint8_t power)
{
    return (uint8_t)(128*power/100);
}

void IO_RC3_CallBack(void)
{
    //LATE = (LATE | 0x0400);
    //LATE =  LATE ^ 0x0400;
    COMPA_flag = 1;
}

void IO_RD10_CallBack(void)
{
    COMPB_flag = 1;
}


void IO_RD11_CallBack(void)
{
    COMPC_flag = 1;
}

void MCP802X_FAULT_CallBack(void)
{
    fault_flag = 1;
}

void Sine_NoFeedBack()
{
    char cnt_a = 0;
    char cnt_b = 0;
    char cnt_c = 0;
    int ph_a, ph_b, ph_c;
    

    while(1)
    {
        ph_a = Get_Duty(sine_wave[cnt_a]*Motor_Power/128);
        ph_b = Get_Duty(sine_wave[cnt_b]*Motor_Power/128);
        ph_c = Get_Duty(sine_wave[cnt_c]*Motor_Power/128);
        
        //printf("ph %d\r\n", ph_a);
    
        PWM_DutyCycleSet(PWM_GENERATOR_1, ph_a);
        PWM_DutyCycleSet(PWM_GENERATOR_2, ph_b);
        PWM_DutyCycleSet(PWM_GENERATOR_3, ph_c);
        
        
        cnt_a++;
        cnt_a = cnt_a%24;
        cnt_b = (cnt_a + 8)%24;
        cnt_c = (cnt_a + 16)%24;

        
        LATE = (LATE & ~0x0400);
        DELAY_milliseconds(1);
        
        if(fault_flag == 100)
        {

            
            //break;
        }
    }
    
    while(1);
    
    
}

void PWM_PinMode_Enable(enum PWM_GENERATOR genNum)
{
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_PinMode_Disable(enum PWM_GENERATOR genNum)
{
    PWM_OverrideHighDisable(genNum);
    PWM_OverrideLowDisable(genNum);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_Set_HiZ(enum PWM_GENERATOR genNum)
{
    PWM_OverrideDataHighSet(genNum, false);
    PWM_OverrideDataLowSet(genNum, false);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_Pin_SetLowSide(enum PWM_GENERATOR genNum)
{
    PWM_OverrideDataHighSet(genNum, false);
    PWM_OverrideDataLowSet(genNum, true);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_Pin_SetHighSide(enum PWM_GENERATOR genNum)
{
    PWM_OverrideDataHighSet(genNum, true);
    PWM_OverrideDataLowSet(genNum, false);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_ResetAll()
{
    PWM_PinMode_Disable(PWM_GENERATOR_1);
    PWM_PinMode_Disable(PWM_GENERATOR_2);
    PWM_PinMode_Disable(PWM_GENERATOR_3);
}

void Square_Pulse()
{
    char cnt_a = 0;
    char cnt_b = 0;
    char cnt_c = 0;
    int ph_abc, ph_N;
    
    
    uint16_t speed = 10;//ms
    
    Motor_Power = 30;
    
    ph_abc = Get_Duty(Motor_Power);
    //ph_N = Get_Duty(0);
    

    PWM_ResetAll();
    
    while(1)
    {
        speed = (uint16_t)(ADC1_ConversionResultGet(0)>>5);
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_2);
        PWM_PinMode_Enable(PWM_GENERATOR_3);
        PWM_DutyCycleSet(PWM_GENERATOR_1, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_2);
        PWM_Set_HiZ(PWM_GENERATOR_3);
        
        DELAY_milliseconds(speed);
        
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_2);
        PWM_PinMode_Enable(PWM_GENERATOR_3);
        PWM_DutyCycleSet(PWM_GENERATOR_1, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_3);
        PWM_Set_HiZ(PWM_GENERATOR_2);
        
        DELAY_milliseconds(speed);
        
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_1);
        PWM_PinMode_Enable(PWM_GENERATOR_3);
        PWM_DutyCycleSet(PWM_GENERATOR_2, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_3);
        PWM_Set_HiZ(PWM_GENERATOR_1);
        
        DELAY_milliseconds(speed);
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_1);
        PWM_PinMode_Enable(PWM_GENERATOR_3);
        PWM_DutyCycleSet(PWM_GENERATOR_2, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_1);
        PWM_Set_HiZ(PWM_GENERATOR_3);
        
        DELAY_milliseconds(speed);
        
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_1);
        PWM_PinMode_Enable(PWM_GENERATOR_2);
        PWM_DutyCycleSet(PWM_GENERATOR_3, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_1);
        PWM_Set_HiZ(PWM_GENERATOR_2);
        
        DELAY_milliseconds(speed);
        
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_1);
        PWM_PinMode_Enable(PWM_GENERATOR_2);
        PWM_DutyCycleSet(PWM_GENERATOR_3, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_2);
        PWM_Set_HiZ(PWM_GENERATOR_1);
        
        DELAY_milliseconds(speed);
    }
}



void Square_FeedBack()
{
    int ph_abc;
    
    uint16_t speed = 10;//ms
    
    Motor_Power = 50;
    
    ph_abc = Get_Duty(Motor_Power);
    
    
    COMPA_flag = 0;
    COMPB_flag = 0;
    COMPC_flag = 0;
    

    PWM_ResetAll();
    
    while(1)
    {
        Motor_Power = (uint16_t)((ADC1_ConversionResultGet(0)>>5) % 100);
        ph_abc = Get_Duty(Motor_Power);
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_2);
        PWM_PinMode_Enable(PWM_GENERATOR_3);
        PWM_DutyCycleSet(PWM_GENERATOR_1, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_2);
        PWM_Set_HiZ(PWM_GENERATOR_3);
        
        
        while(PORTDbits.RD11 == 1);
//        COMPC_flag = 0;
//        while(COMPC_flag == 0);
        
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_2);
        PWM_PinMode_Enable(PWM_GENERATOR_3);
        PWM_DutyCycleSet(PWM_GENERATOR_1, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_3);
        PWM_Set_HiZ(PWM_GENERATOR_2);
        
        while(PORTDbits.RD10 == 0);
//        COMPB_flag = 0;
//        while(COMPB_flag == 0);

        
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_1);
        PWM_PinMode_Enable(PWM_GENERATOR_3);
        PWM_DutyCycleSet(PWM_GENERATOR_2, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_3);
        PWM_Set_HiZ(PWM_GENERATOR_1);
        
        while(PORTCbits.RC3 == 1);
//        COMPA_flag = 0;
//        while(COMPA_flag == 0);
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_1);
        PWM_PinMode_Enable(PWM_GENERATOR_3);
        PWM_DutyCycleSet(PWM_GENERATOR_2, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_1);
        PWM_Set_HiZ(PWM_GENERATOR_3);
        
        while(PORTDbits.RD11 == 0);
//        COMPC_flag = 0;
//        while(COMPC_flag == 0);
        
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_1);
        PWM_PinMode_Enable(PWM_GENERATOR_2);
        PWM_DutyCycleSet(PWM_GENERATOR_3, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_1);
        PWM_Set_HiZ(PWM_GENERATOR_2);
        
        while(PORTDbits.RD10 == 1);
//        COMPB_flag = 0;
//        while(COMPB_flag == 0);
        
        
        PWM_ResetAll();
        
        PWM_PinMode_Enable(PWM_GENERATOR_1);
        PWM_PinMode_Enable(PWM_GENERATOR_2);
        PWM_DutyCycleSet(PWM_GENERATOR_3, ph_abc);
        PWM_Pin_SetLowSide(PWM_GENERATOR_2);
        PWM_Set_HiZ(PWM_GENERATOR_1);
        
        while(PORTCbits.RC3 == 0);
//        COMPA_flag = 0;
//        while(COMPA_flag == 0);
    }
}


void MOSFET_Signal()
{
    int ph_abc;
    
    uint16_t speed = 10;//ms
    
    Motor_Power = 50;
    
    ph_abc = Get_Duty(Motor_Power);
    
    
    COMPA_flag = 0;
    COMPB_flag = 0;
    COMPC_flag = 0;
    

    PWM_ResetAll();
    
    PWM_PinMode_Enable(PWM_GENERATOR_1);
    
    PWM_PinMode_Enable(PWM_GENERATOR_3);
    
    
    PWM_Pin_SetLowSide(PWM_GENERATOR_1);
    PWM_Set_HiZ(PWM_GENERATOR_3);
    
    while(1)
    {
        Motor_Power = (uint16_t)((ADC1_ConversionResultGet(0)>>5) % 100);
        ph_abc = Get_Duty(Motor_Power);
        
        PWM_DutyCycleSet(PWM_GENERATOR_2, ph_abc);
        DELAY_milliseconds(10);
    }
}

uint8_t rxbuf[10] = {0};
volatile uint8_t rx_int_buf = 0;
volatile uint8_t rx_flag = 0;

int main(void)
{
    SYSTEM_Initialize();
    
    IO_RC3_SetInterruptHandler(IO_RC3_CallBack);
    IO_RD10_SetInterruptHandler(IO_RD10_CallBack);
    IO_RD11_SetInterruptHandler(IO_RD11_CallBack);
            

    
    SCCP1_Timer_Start();
    PWM_Enable();


    char cmd = 0;
    //LATE = 0xffff;
    

    //Sine_NoFeedBack();
    //Square_Pulse();
    Square_FeedBack();
    //MOSFET_Signal();
    
    uint16_t dutyCycle;
    printf("Start.... \r\n");
    
    LATE = 0x0000;
    
    UART1_Write(0x83);
    UART1_Write(0x67);
    DELAY_milliseconds(1);
    printf("rd %x\r\n", rx_int_buf );
    
    rx_flag = 0;
    while(1)
    {
       
        UART1_Write(0x84);
        
        uint8_t rx_cnt = 0;
        
        while(1)
        {
            while(rx_flag == 0);
            if(rx_flag == 1)
            {
                rxbuf[rx_cnt] = rx_int_buf;
                rx_flag = 0;
            }
            
            rx_cnt += 1;
            if(rx_cnt == 3)
                break;
        }
        
       
        printf("rd %x %x %x \r\n", rxbuf[0], rxbuf[1], rxbuf[2] );
        
        //LATE = 0x0000;
        DELAY_milliseconds(10);
    }
    
    while(1)
    {
//        LATE = 0x0400;
//        UART2_Write('a');
//        UART2_Write('\n');
//        DELAY_milliseconds(100);
      //LATE = 0x0000;
      
//        DELAY_milliseconds(100);
         // Add your application code ????
		//cmd = UART2_Read();
       //UART2_Write(cmd);
     // ADC1_SoftwareTriggerEnable();
      //ADC1_SoftwareTriggerEnable();
      //while(ADC1_IsConversionComplete == false){}
        dutyCycle++;
        if(dutyCycle >= 100){
            dutyCycle = 0;
        }
        dutyCycle = (dutyCycle%100);
        PWM_DutyCycleSet(PWM_GENERATOR_3, Get_Duty(dutyCycle));
//        PWM_SoftwareUpdateRequest(PWM_GENERATOR_4);

      int value = ADC1_ConversionResultGet(0);
      //printf("%d\n\r", value);
      DELAY_milliseconds(500);

      
      printf("PER %d\r\n", Get_Duty(dutyCycle));
    }    
}


void UART2_RxCompleteCallback(void)
{ 
    //LATE = 0x0400;
}

void UART1_RxCompleteCallback(void)
{ 
    LATE =  LATE ^ 0x0400;
    rx_int_buf = UART1_Read();
    rx_flag = 1;
} 