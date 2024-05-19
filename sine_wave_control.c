/*
 * File:   sine_wave_control.c
 * Author: btubuntu
 *
 * Created on May 25, 2024, 10:40 PM
 */


#include "main.h"


uint8_t sine_wave[] = {127,121,112,100,88,76,64,52,40,28,16,4,0,4,16,28,40,52,64,76,88,100,112,121};

void Sine_NoFeedBack()
{
    char cnt_a = 0;
    char cnt_b = 0;
    char cnt_c = 0;
    int ph_a, ph_b, ph_c;
    
    //PWM_ResetAll();
    
    uint8_t Motor_Power= 30;
    volatile int speed = 1;

    Motor_Driver_Phase_SetMode(A, PP_PWM);
    Motor_Driver_Phase_SetMode(B, PP_PWM);
    Motor_Driver_Phase_SetMode(C, PP_PWM);
    
    while(1)
    {
        speed = (uint16_t)((ADC1_ConversionResultGet(0)>>5) % 100);
        
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

        
        //LATE = (LATE & ~0x0400);
        DELAY_milliseconds(1);
    }
    
    while(1);
    
    
}