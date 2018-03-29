#ifndef _MOTOR_H
#define _MOTOR_H

#include "head.h"


//Motor 0
#define A1(state) (state>0) ? GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4) :GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0)  //A+
#define B1(state) (state>0) ? GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6) :GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0)  //B+
#define A2(state) (state>0) ? GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5) :GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0)  //A-
#define B2(state) (state>0) ? GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7) :GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0)  //B-

//Motor 1
#define C1(state) (state>0) ? GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0) :GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0)  //C+
#define D1(state) (state>0) ? GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2) :GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0)  //D+
#define C2(state) (state>0) ? GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1) :GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0)  //C-
#define D2(state) (state>0) ? GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3) :GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0)  //D-

void Motor_Configure(void);

//Motor0
void SetMotor_Four_Motor0(uint8_t Direction);
void SetMotor_Eight_Motor0(uint8_t Direction);
//Motor1
void SetMotor_Four_Motor0(uint8_t Direction);
void SetMotor_Eight_Motor0(uint8_t Direction);


#endif
