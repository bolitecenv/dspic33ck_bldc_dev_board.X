/*
 * File:   square_wave_control.c
 * Author: btubuntu
 *
 * Created on May 12, 2024, 10:04 PM
 */


#include "main.h"


//volatile uint8_t Motor_Power = 30;

void Square_Pulse()
{
    int ph_abc;
    
    uint16_t speed = 1000;//ms
    
    ph_abc = 30;
    
    Motor_Driver_Phase_Parameter_Set(A, ph_abc);
    Motor_Driver_Phase_Parameter_Set(B, ph_abc);
    Motor_Driver_Phase_Parameter_Set(C, ph_abc);
    
    while(1)
    {
        speed = (uint16_t)(ADC1_ConversionResultGet(0)>>5);
        
        Motor_Driver_Phase_SetMode(C, PP_HiZ);
        Motor_Driver_Phase_SetMode(B, PP_L);
        Motor_Driver_Phase_SetMode(A, PP_PWM);
        
        DELAY_milliseconds(speed);
        
        Motor_Driver_Phase_SetMode(B, PP_HiZ);
        Motor_Driver_Phase_SetMode(C, PP_L);
        Motor_Driver_Phase_SetMode(A, PP_PWM);
        
        DELAY_milliseconds(speed);
        
        Motor_Driver_Phase_SetMode(A, PP_HiZ);
        Motor_Driver_Phase_SetMode(C, PP_L);
        Motor_Driver_Phase_SetMode(B, PP_PWM);
        
        DELAY_milliseconds(speed);
        
        Motor_Driver_Phase_SetMode(C, PP_HiZ);
        Motor_Driver_Phase_SetMode(A, PP_L);
        Motor_Driver_Phase_SetMode(B, PP_PWM);
        
        DELAY_milliseconds(speed);
        
        Motor_Driver_Phase_SetMode(B, PP_HiZ);
        Motor_Driver_Phase_SetMode(A, PP_L);
        Motor_Driver_Phase_SetMode(C, PP_PWM);
        
        DELAY_milliseconds(speed);
        
        Motor_Driver_Phase_SetMode(A, PP_HiZ);
        Motor_Driver_Phase_SetMode(B, PP_L);
        Motor_Driver_Phase_SetMode(C, PP_PWM);
        
        DELAY_milliseconds(speed);
    }
}



void Square_FeedBack()
{
    int ph_abc;
    
    uint16_t speed = 10;//ms
    
    volatile uint8_t Motor_Power = 50;
    
    ph_abc = Get_Duty(Motor_Power);
    
    
    while(1)
    {
        Motor_Power = (uint16_t)((ADC1_ConversionResultGet(0)>>5) % 100);
        ph_abc = (int)Motor_Power;
        Motor_Driver_Phase_Parameter_Set(A, ph_abc);
        Motor_Driver_Phase_Parameter_Set(B, ph_abc);
        Motor_Driver_Phase_Parameter_Set(C, ph_abc);
        

        
        Motor_Driver_Phase_SetMode(C, PP_HiZ);
        Motor_Driver_Phase_SetMode(B, PP_L);
        Motor_Driver_Phase_SetMode(A, PP_PWM);
        
        
        while(PORTDbits.RD11 == 1);
//        COMPC_flag = 0;
//        while(COMPC_flag == 0);
        
        
        Motor_Driver_Phase_SetMode(B, PP_HiZ);
        Motor_Driver_Phase_SetMode(C, PP_L);
        Motor_Driver_Phase_SetMode(A, PP_PWM);
        
        while(PORTDbits.RD10 == 0);
//        COMPB_flag = 0;
//        while(COMPB_flag == 0);

        
       
        
        Motor_Driver_Phase_SetMode(A, PP_HiZ);
        Motor_Driver_Phase_SetMode(C, PP_L);
        Motor_Driver_Phase_SetMode(B, PP_PWM);
        
        while(PORTCbits.RC3 == 1);
//        COMPA_flag = 0;
//        while(COMPA_flag == 0);
        
        Motor_Driver_Phase_SetMode(C, PP_HiZ);
        Motor_Driver_Phase_SetMode(A, PP_L);
        Motor_Driver_Phase_SetMode(B, PP_PWM);
        
        while(PORTDbits.RD11 == 0);
//        COMPC_flag = 0;
//        while(COMPC_flag == 0);
        
        
        Motor_Driver_Phase_SetMode(B, PP_HiZ);
        Motor_Driver_Phase_SetMode(A, PP_L);
        Motor_Driver_Phase_SetMode(C, PP_PWM);
        
        while(PORTDbits.RD10 == 1);
//        COMPB_flag = 0;
//        while(COMPB_flag == 0);
        
        
        Motor_Driver_Phase_SetMode(A, PP_HiZ);
        Motor_Driver_Phase_SetMode(B, PP_L);
        Motor_Driver_Phase_SetMode(C, PP_PWM);
        
        while(PORTCbits.RC3 == 0);
//        COMPA_flag = 0;
//        while(COMPA_flag == 0);
    }
}