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
#include "main.h"

/*
    Main application
*/


uint8_t fault_flag = 0;

volatile uint8_t COMPA_flag, COMPB_flag, COMPC_flag;

volatile uint8_t Motor_Power = 30;


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
    

    Sine_NoFeedBack();
    //Square_Pulse();
    //Square_Pulse2();
    //Square_FeedBack();
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