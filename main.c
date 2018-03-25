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
#include "head.h"


/**
 * main.c
 */
int main(void)
{
    uint16_t i = 400;

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    Motor_Configure();
    while(i>0)
    {
        SetMotor_Eight(0);
        SysCtlDelay(SysCtlClockGet()*8/(30000));   //╟кед800usкдед1000us
        i--;
    }
  //  return 0;
}
