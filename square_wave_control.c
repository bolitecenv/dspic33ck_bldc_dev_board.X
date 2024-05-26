/*
 * File:   square_wave_control.c
 * Author: btubuntu
 *
 * Created on May 12, 2024, 10:04 PM
 */


#include "main.h"



static uint8_t  Motor_Power;
static uint16_t Motor_Speed;
static uint8_t  motor_square_state;


void motor_square_control_state(uint8_t next_state);


void Square_Control_Setup()
{
    Motor_Power = 20;
    Motor_Speed = 100;
    motor_square_state = 0;

    Motor_Driver_Phase_Parameter_Set(A, Motor_Power);
    Motor_Driver_Phase_Parameter_Set(B, Motor_Power);
    Motor_Driver_Phase_Parameter_Set(C, Motor_Power);
}

void Square_Pulse()
{
    Motor_Speed = (uint16_t)(ADC1_ConversionResultGet(0)>>5);
    
    motor_square_control_state(motor_square_state);

    motor_square_state++;
    motor_square_state = motor_square_state % 6;
    
    DELAY_milliseconds(Motor_Speed);
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