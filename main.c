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
#include <math.h>

/*
    Main application
*/

#define ADC_NUM 256


void MCP_Initialize();

volatile uint32_t timer_1us = 0;

volatile static uint16_t adc_cnt = 0;
volatile static uint16_t adc_buf[ADC_NUM] = {0};
volatile static bool   adc_buf_full = false;
volatile static bool   adc_send_flag = false;

volatile uint8_t rx_flag = 0;
volatile uint8_t rx_error_flag = 0;
volatile uint8_t rx_cmd = 0;
volatile uint8_t rx_error_code = 0;

void MCP8024_Receive_IT_Complete_Callback(void)
{
    rx_flag = 1;
}

void MCP8024_Error_Handler(uint8_t cmd, uint8_t error_code)
{
    rx_error_flag = 1;
    rx_cmd = cmd;
    rx_error_code = error_code;
}

void Phase_Change_callback()
{
    //LATEbits.LATE6 = ~LATEbits.LATE6;
    //adc_send_flag = true;
}

void MCP_Initialize()
{
    MCP8024_CE(CE_OFF);

    uint8_t buf[3] = {0};
    MCP8024_Receive_IT(&buf, 2);

    MCP8024_Send_CMD(MCP8024_SET_CFG_1);
    MCP8024_Send_CMD(0x40);

    while(rx_flag == 0);

    rx_flag = 0;
    printf("received %x %x\r\n", buf[0], buf[1]);
    
    DELAY_milliseconds(3);

    MCP8024_Receive_IT(&buf, 3);
    MCP8024_Send_CMD(MCP8024_GET_CFG_1);

    while(rx_flag == 0);
    printf("received %x %x %x\r\n", buf[0], buf[1], buf[2]);
    
    
    MCP8024_Send_CMD(MCP8024_SET_CFG_0);
    MCP8024_Send_CMD(0x03);

    while(rx_flag == 0);
    rx_flag = 0;
    printf("received %x %x\r\n", buf[0], buf[1]);
    
    DELAY_milliseconds(3);
    
    
    MCP8024_Receive_IT(&buf, 3);
    MCP8024_Send_CMD(MCP8024_GET_CFG_0);

    while(rx_flag == 0);
    printf("received %x %x %x\r\n", buf[0], buf[1], buf[2]);

    MCP8024_CE(CE_ON);
}

int main(void)
{
    SYSTEM_Initialize();
    
//    double a = sin(0.1);
//    uint8_t str[12] = "123456789a";
//    Send_Data(MCP8024_STATUS_0, str, 12);
//    Send_Command(MCP8024_STATUS_0);
//    
            
    //SCCP1_Timer_Start();
    SCCP2_Timer_Start();
    PWM_Enable();

    
    printf("Start.... \r\n");

    MCP_Initialize();
   
    //Sine_NoFeedBack_Setup();
    
    Square_Control_Setup(Phase_Change_callback);
    
    uint16_t loop_cnt = 2000;
    
    while(1)
    {
        //Sine_NoFeedBack();
        //Square_Pulse();
        
        //Square_Hall();
        //Square_FeedBack();
        //Square_ADC_FeedBack(ADC1_ConversionResultGet(Channel_AN0), ADC1_ConversionResultGet(Channel_AN1), ADC1_ConversionResultGet(Channel_AN12));
        
        if(loop_cnt > 0)
        {
            Square_Hall();
            
            uint32_t virtual_neg = ADC1_ConversionResultGet(Channel_AN12) + ADC1_ConversionResultGet(Channel_AN1) + ADC1_ConversionResultGet(Channel_AN0);
            virtual_neg = virtual_neg / 3;
            uint8_t phase_A = 0;
            if(virtual_neg > ADC1_ConversionResultGet(Channel_AN0))
            {
                phase_A = 100;
            }else
            {
                phase_A = 0;
            }
        
            //PWM_DutyCycleSet(PWM_GENERATOR_4, Get_Duty(Scaling100(virtual_neg, 4095*3, 100)));
            PWM_DutyCycleSet(PWM_GENERATOR_4, Get_Duty(phase_A));
            
            loop_cnt--;
        }else{
            //Square_Hall();
            Square_ADC_FeedBack(ADC1_ConversionResultGet(Channel_AN0), ADC1_ConversionResultGet(Channel_AN1), ADC1_ConversionResultGet(Channel_AN12));
        }
        
        


        //DELAY_milliseconds(1);
        //adc_send_flag = true;

        if(rx_error_flag == 1)
        {
            rx_error_flag = 0;
            printf("error: cmd:%x code:%x \r\n",rx_cmd, rx_error_code);
            DELAY_milliseconds(100);
        }
        
        if(adc_buf_full == true)
        {
            for(uint16_t i = 0; i < ADC_NUM; i++)
            {
                // send adc
            }
            adc_buf_full = false;
        }else if(adc_send_flag == true){
            
            //adc_buf[adc_cnt] = ADC1_ConversionResultGet(Channel_AN22);
            
            adc_cnt++;
            if(adc_cnt >= ADC_NUM)
            {
                adc_cnt = 0;
                adc_buf_full = true;

                adc_send_flag = false;
            }
         }
    }
}


void SCCP2_TimeoutCallback (void)
{
    timer_1us++;
}


// PC serial receive complete callback
void UART2_RxCompleteCallback(void)
{ 
    //NOP()
}