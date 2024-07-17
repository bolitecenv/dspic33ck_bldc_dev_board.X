/*
 * File:   mcp8024_driver.c
 * Author: btubuntu
 *
 * Created on May 26, 2024, 12:18 AM
 */

// This MCP8024 driver uses UART1 to communicate.


#include "main.h"

#define RX_BUFFER_SIZE  30

extern volatile uint32_t timer_1us;
static uint32_t motor_delay_before;

volatile static uint8_t rx_flag = 0;

volatile static uint8_t rx_cnt = 0;
volatile static bool    rx_error_flag  = false;
volatile static bool    rx_receive_it_flag = false;
volatile static uint8_t rx_receive_it_cnt = 0;
volatile static uint8_t *p_rx_buf;
volatile static uint8_t rx_buf[RX_BUFFER_SIZE] = {0};



void UART1_RxCompleteCallback(void);
ERROR_CODE status_0_analyzer();
void error_handler(void);

void MCP8024_Send_CMD(uint8_t cmd)
{
    //check if the 1-wire line is in busy state.
    while(MCP8024_isBusy());
    
    UART1_Write(cmd);
}

error_t MCP8024_Receive(uint8_t *buf, uint8_t receive_buf_size, uint16_t time_out)
{
    error_t ret = NG;
    
    rx_receive_it_cnt = receive_buf_size;
    rx_receive_it_flag = true;
    p_rx_buf = buf;
    motor_delay_before = timer_1us;
    
    while(rx_receive_it_flag)
    {
        if( (timer_1us - motor_delay_before) > time_out )
        {
            ret = ERROR_TIMEOUT;
        }
    }
    
    return ret;
}


void MCP8024_Receive_IT(uint8_t *buf, uint8_t receive_buf_size)
{
    rx_receive_it_cnt = receive_buf_size;
    rx_receive_it_flag = true;
    p_rx_buf = buf;
}

void __attribute__ ((weak)) MCP8024_Receive_IT_Complete_Callback(void)
{

}

void __attribute__ ((weak)) MCP8024_Receive_Callback(void)
{

}

void __attribute__ ((weak)) MCP8024_Error_Handler(uint8_t cmd, uint8_t error_code)
{

}

void error_handler()
{
    MCP8024_Error_Handler(rx_buf[0], rx_buf[1]);
}

ERROR_CODE status_0_analyzer()
{
    ERROR_CODE error_code = NormalOperation;
    switch(rx_buf[1])
    {
        case MCP8024_Normal_OP:
            error_code = NormalOperation;
            break;
        case MCP8024_TempWarning:
            error_code = TempWarning;
            break;
        case MCP8024_OverTemp:
            error_code = OverTemp;
            break;
        case MCP8024_UnderVoltage:
            error_code = UnderVoltage;
            break;
        case MCP8024_OverVoltage:
            error_code = OverVoltage;
            break;
        case MCP8024_BR_OverCurrent:
            error_code = BR_OverCurrent;
            break;
        case MCP8024_BR_OutputUnderVoltageWarning:
            error_code = BR_OutputUnderVoltageWarning;
            break;
        case MCP8024_BR_OutputUnderVoltage:
            error_code = BR_OutputUnderVoltage;
            break;
        default:
            error_code = Unregistered;
            break;
    }
    return error_code;
}


void UART1_RxCompleteCallback(void)
{ 
    if(rx_receive_it_flag == true)
    {
        if(rx_receive_it_cnt > 0)
        {
            rx_receive_it_cnt--;
            p_rx_buf[rx_receive_it_cnt] = UART1_Read();

            if(rx_receive_it_cnt == 0)
            {
                rx_receive_it_flag = false;
                MCP8024_Receive_IT_Complete_Callback();
            }
            
        }else{
            rx_receive_it_flag = false;
            MCP8024_Receive_IT_Complete_Callback();
        }
    }else{
        if(rx_cnt >= RX_BUFFER_SIZE)
        {
            rx_error_flag = 1;
        }else{
            uint8_t rx_buf_tmp = UART1_Read();
            if(rx_buf_tmp == MCP8024_STATUS_0 || rx_buf_tmp == MCP8024_STATUS_1)
            {
                if(rx_cnt == 0)
                {
                    rx_buf[rx_cnt] = rx_buf_tmp;
                    rx_cnt++;
                }
            }else{
                if(rx_cnt == 1)
                {
                    rx_buf[rx_cnt] = rx_buf_tmp;
                    error_handler();
                    rx_cnt = 0;
                }
            }
        }
        //MCP8024_Receive_Callback();
    }   
}