/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MOTOR_DRIVER_H
#define	MOTOR_DRIVER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>

#include "mcc_generated_files/pwm_hs/pwm.h"
#include "mcc_generated_files/pwm_hs/pwm_hs_interface.h"

#define PWM_MA PWM_GENERATOR_1
#define PWM_MB PWM_GENERATOR_2
#define PWM_MC PWM_GENERATOR_3


typedef struct IO_INT
{
    volatile uint8_t MOTOR_A;
    volatile uint8_t MOTOR_B;
    volatile uint8_t MOTOR_C;
}motor_driver_interrupt_st;


typedef struct motor_base
{
    uint8_t     power;// 0-100 : motor power output
    uint8_t     duty;// 0-100 :
    volatile    uint16_t    adc_value;
    uint16_t    adc_pin;
    uint16_t    io_int_pin;
    volatile    uint8_t     io_flag;
    enum        PWM_GENERATOR   pwm_generator;
}motor_phase_st;


typedef enum
{
    A =  1,
    B,
    C
}Motor_Phase;

typedef enum
{
    PP_HiZ = 1,
    PP_H,
    PP_L,
    PP_PWM
}PP_MODE;


void Motor_Driver_Init(Motor_Phase motor_phase);
enum PWM_GENERATOR Motor_Driver_GetPWMNumFromPhase(Motor_Phase motor_phase);
void Motor_Driver_Phase_Parameter_Set(Motor_Phase motor_phase, uint8_t value);
void Motor_Driver_Phase_SetMode(Motor_Phase motor_phase, PP_MODE pp_mode);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

