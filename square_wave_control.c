/*
 * File:   square_wave_control.c
 * Author: btubuntu
 *
 * Created on May 12, 2024, 10:04 PM
 */


#include "main.h"
#include "tools.h"

#define IO_HALL_A   PORTBbits.RB5 // HALL U
#define IO_HALL_B   PORTBbits.RB6
#define IO_HALL_C   PORTDbits.RD5 // HALL W

extern volatile uint32_t timer_1us;

static uint8_t  Motor_Power;
static uint16_t Motor_Speed;
static uint8_t  motor_square_state;
static uint8_t  motor_delay_flag;
static uint8_t  motor_phase_change_flag;

static uint32_t motor_delay_before;
static uint32_t motor_speed_us;
static uint32_t motor_phase_change_before_us;



static uint8_t IO_HALL_A_before = 0;
static uint8_t IO_HALL_B_before = 0;
static uint8_t IO_HALL_C_before = 0;

void motor_square_control_state(uint8_t next_state);

void IO_RC3_CallBack(void)
{

}

void IO_RD10_CallBack(void)
{

}


void IO_RD11_CallBack(void)
{

}

static void (*Step_Change_callback)(void) = NULL;


void Square_Control_Setup(void (*step_change_callback)(void))
{
    Step_Change_callback = step_change_callback;

    IO_RC3_SetInterruptHandler(IO_RC3_CallBack);
    IO_RD10_SetInterruptHandler(IO_RD10_CallBack);
    IO_RD11_SetInterruptHandler(IO_RD11_CallBack);
    
    
    Motor_Power = 20; // Set motor power 0-100.
    Motor_Speed = 10; // 10 ms to change the motor state.
    motor_square_state = 0; // Motor state 0-5
    motor_delay_flag = 0;
    motor_delay_before = 0;
    motor_speed_us = 0;
    motor_phase_change_before_us = 0;
    motor_phase_change_flag = 0;

    Motor_Driver_Phase_Parameter_Set(A, Motor_Power);
    Motor_Driver_Phase_Parameter_Set(B, Motor_Power);
    Motor_Driver_Phase_Parameter_Set(C, Motor_Power);
}

void Square_Pulse()
{
    // Check if the required time has passed to change the motor state.
    if(motor_delay_flag == 0)
    {
        // Scale the ADC 12 bit value to 0-100
        Motor_Power = Scaling100(ADC1_ConversionResultGet(Channel_AN22), 4095, 100);

        // Update motor power
        Motor_Driver_Phase_Parameter_Set(A, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(B, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(C, Motor_Power);
        
        // Move the state
        motor_square_control_state(motor_square_state);

        motor_square_state++;
        motor_square_state = motor_square_state % 6; // State will rotate the value from 0 to 5.

        motor_delay_before = timer_1us; // Get the timer to caluculate the elapsed time.
        motor_speed_us = Motor_Speed*1000; // Make the motor speed in microseconds, as Motor_Speed is in milliseconds.
        
        // If the motor state changes, the callback is called.
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
}

void Square_Hall()
{
    Motor_Power = Scaling100(ADC1_ConversionResultGet(Channel_AN22), 4095, 100);
        Motor_Driver_Phase_Parameter_Set(A, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(B, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(C, Motor_Power);
    
        motor_square_control_state(motor_square_state);

        switch(motor_square_state)
        {
                case 0:
                        while(IO_HALL_B == 1);
                        break;
                case 1:
                        while(IO_HALL_C == 0);
                        break;
                case 2:
                        while(IO_HALL_A == 1);
                        break;
                case 3:
                        while(IO_HALL_B == 0);
                        break;
                case 4:
                        while(IO_HALL_C == 1);
                        break;
                case 5:
                        while(IO_HALL_A == 0);
                        break;
        }
        motor_square_state++;
        motor_square_state = motor_square_state % 6;
        
        if(motor_square_state == 0)
        {
            LATEbits.LATE6 = 1;
            // If the motor state changes, the callback is called.
            if(NULL != Step_Change_callback)
            {
                (*Step_Change_callback)();
            }
        }else if(motor_square_state == 3){
            LATEbits.LATE6 = 0;
            // If the motor state changes, the callback is called.
            if(NULL != Step_Change_callback)
            {
                (*Step_Change_callback)();
            }

        }
        
        motor_phase_change_before_us = timer_1us;
}


void Square_ADC_FeedBack(uint16_t PhaseA_val, uint16_t PhaseB_val, uint16_t PhaseC_val)
{
    if (motor_delay_flag == 1)
    {
        if((timer_1us - motor_delay_before) > motor_speed_us)
        {
                motor_delay_flag = 0;
                motor_phase_change_flag = 0;
                
                motor_square_state++;
            motor_square_state = motor_square_state % 6;
            
            motor_square_control_state(motor_square_state);
            
            Motor_Power = Scaling100(ADC1_ConversionResultGet(Channel_AN22), 4095, 100);
            Motor_Driver_Phase_Parameter_Set(A, Motor_Power);
            Motor_Driver_Phase_Parameter_Set(B, Motor_Power);
            Motor_Driver_Phase_Parameter_Set(C, Motor_Power);
            
         
            motor_phase_change_before_us = timer_1us;
            
            
            motor_delay_flag = 0;
            motor_phase_change_flag = 1;
        }else{
            return;
        }
    }
    
        uint32_t virtual_neg = PhaseA_val + PhaseB_val + PhaseC_val;
        virtual_neg = virtual_neg / 3;
        uint8_t phase_A = 0;
        if(virtual_neg > PhaseB_val)
        {
            phase_A = 100;
        }else
        {
            phase_A = 0;
        }
        PWM_DutyCycleSet(PWM_GENERATOR_4, Get_Duty(phase_A));

        uint8_t wari = 6;
        
 
        switch(motor_square_state)
        {
                case 0:
                        if(IO_HALL_B == 0){
                            motor_delay_flag = 1;
                            motor_delay_before = timer_1us; // Get the timer to caluculate the elapsed time.
                            motor_speed_us = timer_1us - motor_phase_change_before_us; // Make the motor speed in microseconds, as Motor_Speed is in milliseconds.
            motor_speed_us = motor_speed_us / wari;
                            LATEbits.LATE6 = 0;
                        }
                        break;
                case 1:
                        if(IO_HALL_C == 1){
                            motor_delay_flag = 1;
                            motor_delay_before = timer_1us; // Get the timer to caluculate the elapsed time.
                            motor_speed_us = timer_1us - motor_phase_change_before_us; // Make the motor speed in microseconds, as Motor_Speed is in milliseconds.
            motor_speed_us = motor_speed_us / wari;
                        }
                        break;
                case 2:
                        if(IO_HALL_A == 0){
                            motor_delay_flag = 1;
                            motor_delay_before = timer_1us; // Get the timer to caluculate the elapsed time.
                            motor_speed_us = timer_1us - motor_phase_change_before_us; // Make the motor speed in microseconds, as Motor_Speed is in milliseconds.
            motor_speed_us = motor_speed_us / wari;
                        }
                        break;
                case 3:
                        if(IO_HALL_B == 1){
                            motor_delay_flag = 1;
                            motor_delay_before = timer_1us; // Get the timer to caluculate the elapsed time.
                            motor_speed_us = timer_1us - motor_phase_change_before_us; // Make the motor speed in microseconds, as Motor_Speed is in milliseconds.
            motor_speed_us = motor_speed_us / wari;
                        }
                        break;
                case 4:
                        if(IO_HALL_C == 0){
                            motor_delay_flag = 1;
                            motor_delay_before = timer_1us; // Get the timer to caluculate the elapsed time.
                            motor_speed_us = timer_1us - motor_phase_change_before_us; // Make the motor speed in microseconds, as Motor_Speed is in milliseconds.
            motor_speed_us = motor_speed_us / wari;
                        }
                        break;
                case 5:
                        if(IO_HALL_A == 1){
                            motor_delay_flag = 1;
                            motor_delay_before = timer_1us; // Get the timer to caluculate the elapsed time.
                            motor_speed_us = timer_1us - motor_phase_change_before_us; // Make the motor speed in microseconds, as Motor_Speed is in milliseconds.
            motor_speed_us = motor_speed_us / wari;
                            LATEbits.LATE6 = 1;
                        }
                        break;
        }
        
        
        
        if(motor_phase_change_flag == 0){
            
            
        }
        
        
        return;
    
        
        
        

        switch(motor_square_state)
        {
                case 0:
                    if(IO_HALL_B == 0)
                        motor_delay_flag = 1;
//                    if(virtual_neg > PhaseC_val)       
//                        motor_delay_flag = 1;
                    break;
                case 1:
//                    if(virtual_neg < PhaseB_val)
//                        motor_delay_flag = 1;
                    if(IO_HALL_C == 1)
                        motor_delay_flag = 1;
                    break;
                case 2:
//                    if(virtual_neg > PhaseA_val)
//                        motor_delay_flag = 1;
                    if(IO_HALL_A == 0)
                        motor_delay_flag = 1;
                    break;
                case 3:
//                    if(virtual_neg < PhaseC_val)
//                        motor_delay_flag = 1;
                    if(IO_HALL_B == 1)
                        motor_delay_flag = 1;
                    break;
                case 4:
//                    if(virtual_neg > PhaseB_val)
//                        motor_delay_flag = 1;
                    if(IO_HALL_C == 0)
                        motor_delay_flag = 1;
                    break;
                case 5:
//                    if(virtual_neg < PhaseA_val)
//                        motor_delay_flag = 1;
                    if(IO_HALL_A == 1)
                        motor_delay_flag = 1;
                    break;
        }
        
        if(motor_delay_flag == 0){
            return;
        }
        
        motor_square_control_state(motor_square_state);
        
        motor_square_state++;
        motor_square_state = motor_square_state % 6;
        
        motor_delay_before = timer_1us; // Get the timer to caluculate the elapsed time.
        motor_speed_us = timer_1us - motor_phase_change_before_us; // Make the motor speed in microseconds, as Motor_Speed is in milliseconds.
        motor_speed_us = motor_speed_us / 2;
        motor_phase_change_before_us = timer_1us;
        
        
        Motor_Power = Scaling100(ADC1_ConversionResultGet(Channel_AN22), 4095, 100);
        Motor_Driver_Phase_Parameter_Set(A, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(B, Motor_Power);
        Motor_Driver_Phase_Parameter_Set(C, Motor_Power);
        
        
        motor_phase_change_flag = 1;
        motor_delay_flag = 0;
}



void Square_FeedBack()
{
        Motor_Power = Scaling100(ADC1_ConversionResultGet(Channel_AN22), 4095, 100);
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