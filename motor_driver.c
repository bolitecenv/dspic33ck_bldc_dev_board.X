/*
 * File:   motor_driver.c
 * Author: btubuntu
 *
 * Created on May 19, 2024, 11:38 PM
 */


#include "main.h"


motor_phase_st motor_phase_a_configs, motor_phase_b_configs, motor_phase_c_configs;

void Motor_Driver_Init(Motor_Phase motor_phase)
{
    PWM_Enable();
    
    motor_phase_st _configs;
    _configs.duty = 0;
    _configs.adc_value = 0;
    _configs.io_flag = 0;
    _configs.io_int_pin = 0;
    _configs.adc_pin = 0;
    _configs.power = 0;
    
    
    switch(motor_phase)
    {
        case A:
            memcpy(&motor_phase_a_configs, &_configs, sizeof(_configs));
            break;
        case B:
            memcpy(&motor_phase_b_configs, &_configs, sizeof(_configs));
            break;
        case C:
            memcpy(&motor_phase_c_configs, &_configs, sizeof(_configs));
            break;
    }
    
}

enum PWM_GENERATOR Motor_Driver_GetPWMNumFromPhase(Motor_Phase motor_phase)
{
    switch(motor_phase)
    {
        case A:
            return PWM_GENERATOR_1;//motor_phase_a_configs.pwm_generator;
            break;
        case B:
            return PWM_GENERATOR_2;// motor_phase_b_configs.pwm_generator;
            break;
        case C:
            return PWM_GENERATOR_3;//motor_phase_c_configs.pwm_generator;
            break;
    }
}

void Motor_Driver_Phase_Parameter_Set(Motor_Phase motor_phase, uint8_t value)
{
    enum PWM_GENERATOR pwm_generator = Motor_Driver_GetPWMNumFromPhase(motor_phase);
    PWM_DutyCycleSet(pwm_generator, Get_Duty(value));
}


void Motor_Driver_Phase_SetMode(Motor_Phase motor_phase, PP_MODE pp_mode)
{
    enum PWM_GENERATOR pwm_generator = Motor_Driver_GetPWMNumFromPhase(motor_phase);
    
    //PWM_PinMode_Disable(pwm_generator);
    
    switch(pp_mode)
    {
        case PP_HiZ:
            PWM_PinMode_Enable(pwm_generator);
            PWM_Set_HiZ(pwm_generator);
            break;
        case PP_H:
            PWM_PinMode_Enable(pwm_generator);
            PWM_Pin_SetHighSide(pwm_generator);
            break;
        case PP_L:
            PWM_PinMode_Enable(pwm_generator);
            PWM_Pin_SetLowSide(pwm_generator);
            break;
        case PP_PWM:
            PWM_PinMode_Disable(pwm_generator);
            break;
    }
}