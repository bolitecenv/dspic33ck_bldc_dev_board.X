/*
 * File:   square_wave_control.c
 * Author: btubuntu
 *
 * Created on May 12, 2024, 10:04 PM
 */


#include "main.h"


volatile uint8_t Motor_Power = 30;

void Square_Pulse()
{
    int ph_abc;
    
    
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
