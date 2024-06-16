/*
 * File:   square_wave_control.c
 * Author: btubuntu
 *
 * Created on May 12, 2024, 10:04 PM
 */


#include "main.h"


extern volatile uint32_t timer_1us;

static uint8_t  Motor_Power;
static uint16_t Motor_Speed;
static uint8_t  motor_square_state;
static uint8_t  motor_delay_flag;

static uint32_t motor_delay_before;
static uint32_t motor_speed_us;

void motor_square_control_state(uint8_t next_state);

static void (*Step_Change_callback)(void) = NULL;


void Square_Control_Setup(void (*step_change_callback)(void))
{
    Step_Change_callback = step_change_callback;
    
    
    Motor_Power = 20;
    Motor_Speed = 20;
    motor_square_state = 0;
    motor_delay_flag = 0;
    motor_delay_before = 0;
    motor_speed_us = 0;

    Motor_Driver_Phase_Parameter_Set(A, Motor_Power);
    Motor_Driver_Phase_Parameter_Set(B, Motor_Power);
    Motor_Driver_Phase_Parameter_Set(C, Motor_Power);
}

void Square_Pulse()
{
    if(motor_delay_flag == 0)
    {
        Motor_Power = (uint16_t)(ADC1_ConversionResultGet(0)>>5);
        Motor_Driver_Phase_Parameter_Set(A, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(B, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(C, Motor_Power);
    
        motor_square_control_state(motor_square_state);

        motor_square_state++;
        motor_square_state = motor_square_state % 6;

        motor_delay_before = timer_1us;
        motor_speed_us = Motor_Speed*1000;
        
        
        if(NULL != Step_Change_callback)
        {
            (*Step_Change_callback)();
        }

        motor_delay_flag = 1;
    }else{
        if((timer_1us - motor_delay_before) > motor_speed_us)
        {
                motor_delay_flag = 0;
        }
    }
    
    
    //DELAY_milliseconds(Motor_Speed);
}



void Square_FeedBack()
{
        Motor_Power = (uint16_t)(ADC1_ConversionResultGet(0)>>5);
        Motor_Driver_Phase_Parameter_Set(A, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(B, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(C, Motor_Power);
    
        motor_square_control_state(motor_square_state);

        switch(motor_square_state)
        {
                case 0:
                        while(PORTDbits.RD11 == 1);
                        break;
                case 1:
                        while(PORTDbits.RD10 == 0);
                        break;
                case 2:
                        while(PORTCbits.RC3 == 1);
                        break;
                case 3:
                        while(PORTDbits.RD11 == 0);
                        break;
                case 4:
                        while(PORTDbits.RD10 == 1);
                        break;
                case 5:
                        while(PORTCbits.RC3 == 0);
                        break;
        }
        motor_square_state++;
        motor_square_state = motor_square_state % 6;
}


void motor_square_control_state(uint8_t next_state)
{
        switch(next_state)
        {
                case 0:
                        Motor_Driver_Phase_SetMode(C, PP_HiZ);
                        Motor_Driver_Phase_SetMode(B, PP_L);
                        Motor_Driver_Phase_SetMode(A, PP_PWM);
                        break;
                case 1:
                        Motor_Driver_Phase_SetMode(B, PP_HiZ);
                        Motor_Driver_Phase_SetMode(C, PP_L);
                        Motor_Driver_Phase_SetMode(A, PP_PWM);
                        break;
                case 2:
                        Motor_Driver_Phase_SetMode(A, PP_HiZ);
                        Motor_Driver_Phase_SetMode(C, PP_L);
                        Motor_Driver_Phase_SetMode(B, PP_PWM);
                        break;
                case 3:
                        Motor_Driver_Phase_SetMode(C, PP_HiZ);
                        Motor_Driver_Phase_SetMode(A, PP_L);
                        Motor_Driver_Phase_SetMode(B, PP_PWM);
                        break;
                case 4:
                        Motor_Driver_Phase_SetMode(B, PP_HiZ);
                        Motor_Driver_Phase_SetMode(A, PP_L);
                        Motor_Driver_Phase_SetMode(C, PP_PWM);
                        break;
                case 5:
                        Motor_Driver_Phase_SetMode(A, PP_HiZ);
                        Motor_Driver_Phase_SetMode(B, PP_L);
                        Motor_Driver_Phase_SetMode(C, PP_PWM);
                        break;
        }
}