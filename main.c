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


void IO_RC3_CallBack(void)
{

}

void IO_RD10_CallBack(void)
{

}


void IO_RD11_CallBack(void)
{

}

volatile uint32_t timer_1us = 0;

volatile static uint8_t adc_cnt = 0;
volatile static uint16_t adc_buf[500] = {0};
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
    adc_send_flag = true;
}

int main(void)
{
    SYSTEM_Initialize();
    
    IO_RC3_SetInterruptHandler(IO_RC3_CallBack);
    IO_RD10_SetInterruptHandler(IO_RD10_CallBack);
    IO_RD11_SetInterruptHandler(IO_RD11_CallBack);
            
    //SCCP1_Timer_Start();
    SCCP2_Timer_Start();
    PWM_Enable();


    printf("Start.... \r\n");
    
    LATE = LATE & 0x0000;

    uint8_t buf[3] = {0};
    MCP8024_Recieve_IT(&buf, 2);

    MCP8024_Send_CMD(MCP8024_SET_CFG_1);
    MCP8024_Send_CMD(0x40);

    while(rx_flag == 0);

    rx_flag = 0;
    printf("received %x %x\r\n", buf[0], buf[1]);
    
    DELAY_milliseconds(3);

    MCP8024_Recieve_IT(&buf, 3);
    MCP8024_Send_CMD(MCP8024_GET_CFG_1);

    while(rx_flag == 0);
    printf("received %x %x %x\r\n", buf[0], buf[1], buf[2]);
    
    
    MCP8024_Send_CMD(MCP8024_SET_CFG_0);
    MCP8024_Send_CMD(0x03);

    while(rx_flag == 0);
    rx_flag = 0;
    printf("received %x %x\r\n", buf[0], buf[1]);
    
    DELAY_milliseconds(3);
    
    
    MCP8024_Recieve_IT(&buf, 3);
    MCP8024_Send_CMD(MCP8024_GET_CFG_0);

    while(rx_flag == 0);
    printf("received %x %x %x\r\n", buf[0], buf[1], buf[2]);
    
    LATE = PORTE | 0x0010;
    //DMA_ChannelEnable(DMA_CHANNEL_0);
    //DMA_TransferCountSet
    //DMA_SourceAddressSet()
    //DMA_DestinationAddressSet
    
    //DMA_SoftwareTriggerEnable(DMA_CHANNEL_0);

    //Sine_NoFeedBack_Setup();
    Square_Control_Setup(Phase_Change_callback);
    
    while(1)
    {
        //Sine_NoFeedBack();
        Square_Pulse();
        //Square_FeedBack();
        
        //printf("%ld\n", timer_1us);

        

        if(rx_error_flag == 1)
        {
            rx_error_flag = 0;
            printf("error: cmd:%x code:%x \r\n",rx_cmd, rx_error_code);
            DELAY_milliseconds(100);
        }
        
        if(adc_buf_full == true)
        {
            for(uint16_t i = 0; i < 256; i++)
            {
                uint8_t temp = (uint8_t)(adc_buf[i] >> 4);
                UART2_Write(temp);
                //printf("%d\n", adc_buf[i]);
            }
            UART2_Write('\n');
            adc_buf_full = false;
        }else if(adc_send_flag == true){
           adc_buf[adc_cnt] = ADC1_ConversionResultGet(Channel_AN22);//ADC1_ConversionResultGet(Channel_AN0);
           adc_cnt++;
           if(adc_cnt >= 0xff)
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
    // adc_buf[adc_cnt] = ADC1_ConversionResultGet(Channel_AN0);
    // adc_cnt++;
    // if(adc_cnt == 0xff)
    // {
    //     adc_cnt = 0;
    //     adc_buf_full = true;
    // }
}


void UART2_RxCompleteCallback(void)
{ 
    //LATE = 0x0400;
}