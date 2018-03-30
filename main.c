#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "Motor/motor.h"
#include "delay/delay.h"
#include "uart/uart.h"
#include "head.h"
#include "Timer/Timer.h"

extern uint32_t Counter;
extern uint8_t MotorOrderDirection;        //前：0  后：1  左：2  右： 3
extern uint8_t MotorOrderDisplacement;     //前后表示距离，左右表示转向角
uint32_t CountBan = 65335;                 //Counter最大值65535，计数一圈6400故，有效计数为10圈，即200cm
/**
 * main.c
 */
int main(void)
{
    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    FPULazyStackingEnable();
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Enable the GPIO pins for the LED (PF2).
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_1);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

    Uart0Iint();
    Uart1Iint();
    MotorInit();
    MotorContolTimer();
    MotorSet(3,0,0);

    while(1)
    {
        if(MotorOrderDirection==0)  //F
        {
           // Counter = 0; //计数清零
            MotorSet(2,0,1);
        }
        if(MotorOrderDirection==1)  //B
        {
           // Counter = 0; //计数清零
            MotorSet(2,1,0);
        }
        if(MotorOrderDirection==2)  //L
        {
           // Counter = 0; //计数清零
            MotorSet(1,0,1);
        }
        if(MotorOrderDirection==3)  //R
        {
           // Counter = 0; //计数清零
            MotorSet(0,0,1);
        }
        //计算公式：200步一转，一转20cm,32细分；Distance = 20*Counter/(200*32)；
        if(MotorOrderDirection==0||MotorOrderDirection==1)
        {
            CountBan = MotorOrderDisplacement*10*32;
        }
        //计算公式；轮距16cm，1/4弧长为25.1327cm，对应20cm为400步可求得1/4弧长为251步可知每十弧度27.888889步
        else if (MotorOrderDirection==2||MotorOrderDirection==3)
        {
            CountBan = (int)MotorOrderDisplacement*2.788889*32;
        }

        if(Counter>CountBan)
        {
            Counter = 0; //计数清零
            MotorSet(3,0,0);//制动
            TimerDisable(TIMER0_BASE, TIMER_A);

        }
    }

  //  return 0;
}
