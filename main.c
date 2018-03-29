#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
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


/**
 * main.c
 */
int main(void)
{
    uint16_t i = 400;
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    Motor_Configure();
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Enable the GPIO pins for the LED (PF2).
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2|GPIO_PIN_1);

    Uart0Iint();
    Uart1Iint();
    while(i>0)
    {
        SetMotor_Eight_Motor0(0);
        SysCtlDelay(SysCtlClockGet()*8/(30000));   //╟кед800usкдед1000us
        i--;
    }
    i=400;
    while(i>0)
    {
        SetMotor_Eight_Motor0(1);
        SysCtlDelay(SysCtlClockGet()*8/(30000));   //╟кед800usкдед1000us
        i--;
    }
    i=400;
    while(i>0)
    {
        SetMotor_Eight_Motor1(0);
        SysCtlDelay(SysCtlClockGet()*8/(30000));   //╟кед800usкдед1000us
        i--;
    }
    i=400;
    while(i>0)
    {
        SetMotor_Eight_Motor1(1);
        SysCtlDelay(SysCtlClockGet()*8/(30000));   //╟кед800usкдед1000us
        i--;
    }
  //  return 0;
}
