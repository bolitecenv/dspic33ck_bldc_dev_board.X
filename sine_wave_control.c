/*
 * File:   sine_wave_control.c
 * Author: btubuntu
 *
 * Created on May 25, 2024, 10:40 PM
 */


#include "main.h"


static uint8_t sine_wave[] = {127,121,112,100,88,76,64,52,40,28,16,4,0,4,16,28,40,52,64,76,88,100,112,121};
static uint16_t ph_a, ph_b, ph_c;
static uint8_t cnt_a, cnt_b, cnt_c;
static uint8_t Motor_Power;
static uint16_t Motor_Speed;


void Sine_NoFeedBack_Setup()
{
    cnt_a = 0;
    cnt_b = 0;
    cnt_c = 0;
    ph_a = 0;
    ph_b = 0;
    ph_c = 0;

    Motor_Power = 30;
    Motor_Speed = 100;

    Motor_Driver_Phase_SetMode(A, PP_PWM);
    Motor_Driver_Phase_SetMode(B, PP_PWM);
    Motor_Driver_Phase_SetMode(C, PP_PWM);
}

void Sine_NoFeedBack()
{
    

    Motor_Speed = (uint16_t)((ADC1_ConversionResultGet(0)>>5) % 100);
        
    ph_a = (uint8_t)(sine_wave[cnt_a]*Motor_Power/128);
    ph_b = (uint8_t)(sine_wave[cnt_b]*Motor_Power/128);
    ph_c = (uint8_t)(sine_wave[cnt_c]*Motor_Power/128);
    
    //printf("ph %d\r\n", ph_a);

    Motor_Driver_Phase_Parameter_Set(A, ph_a);
    Motor_Driver_Phase_Parameter_Set(B, ph_b);
    Motor_Driver_Phase_Parameter_Set(C, ph_c);

    
    cnt_a++;
    cnt_a = cnt_a%24;
    cnt_b = (cnt_a + 8)%24;
    cnt_c = (cnt_a + 16)%24;


    DELAY_milliseconds(Motor_Speed);
}