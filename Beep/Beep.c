#include "beep.h"

void Beep_Configure()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    //���GPIO����
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_6);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0);
}
