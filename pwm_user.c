/*
 * File:   pwm_user.c
 * Author: btubuntu
 *
 * Created on May 12, 2024, 10:23 PM
 */


#include "main.h"

uint16_t Get_Duty(uint8_t duty)
{
    return (uint16_t)(PG1PER/100*duty);
}

uint8_t Get_Power(uint8_t power)
{
    return (uint8_t)(128*power/100);
}



void PWM_PinMode_Enable(enum PWM_GENERATOR genNum)
{
    PWM_OverrideHighEnable(genNum);
    PWM_OverrideLowEnable(genNum);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_PinMode_Disable(enum PWM_GENERATOR genNum)
{
    PWM_OverrideHighDisable(genNum);
    PWM_OverrideLowDisable(genNum);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_Set_HiZ(enum PWM_GENERATOR genNum)
{
    PWM_OverrideDataHighSet(genNum, false);
    PWM_OverrideDataLowSet(genNum, false);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_Pin_SetLowSide(enum PWM_GENERATOR genNum)
{
    PWM_OverrideDataHighSet(genNum, false);
    PWM_OverrideDataLowSet(genNum, true);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_Pin_SetHighSide(enum PWM_GENERATOR genNum)
{
    PWM_OverrideDataHighSet(genNum, true);
    PWM_OverrideDataLowSet(genNum, false);
    PWM_SoftwareUpdateRequest(genNum);
}

void PWM_ResetAll()
{
    PWM_PinMode_Disable(PWM_GENERATOR_1);
    PWM_PinMode_Disable(PWM_GENERATOR_2);
    PWM_PinMode_Disable(PWM_GENERATOR_3);
}