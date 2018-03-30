#include "timer.h"

extern uint8_t MotorOrderDirection;        //前：0  后：1  左：2  右： 3
extern uint8_t MotorOrderDisplacement;     //前后表示距离，左右表示转向角
char Time_Flag = 0;
uint32_t Counter = 0;

//如果两个定时器的效果不明显，可以使用一个定时器通过改变计数值来控制两个电机！！
void MotorContolTimer(void)
{
    //
       // Enable the peripherals used by this example.
       //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

       //
       // Enable processor interrupts.
       //
        IntMasterEnable();

       //
       // Configure the two 32-bit periodic timers.
       //
        TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
        TimerLoadSet(TIMER0_BASE, TIMER_A,  SysCtlClockGet()/20000-1);  //10KHz

       //
       // Setup the interrupts for the timer timeouts.
       //
        IntEnable(INT_TIMER0A);
        TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

       //
       // Enable the timers.
       //
        TimerEnable(TIMER0_BASE, TIMER_A);
}
void Timer0IntHandler(void)
{
    //清除标志位
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    IntMasterDisable();
    Time_Flag++;
    if(Time_Flag>1)
        Time_Flag = 0;
    if(Time_Flag>0)
    {
        Counter++;
        if(Counter>65535)
            Counter=0;
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);//执行脉冲来控制转速
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);//执行脉冲来控制转速
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);

    }
    else
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);//执行脉冲来控制转速
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);//执行脉冲来控制转速

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

    }
    IntMasterEnable();

}

//void Motor1_Contol(void)
//{
//    //使能TIMER1
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
//    //TimerConfigure(TIMER1_BASE, TIMER_CFG_ONE_SHOT);//单次计数模式
//    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);//周期性计数模式
//    TimerLoadSet(TIMER1_BASE, TIMER_A,SysCtlClockGet() / 10 - 1);//计数频率10HZ
//    IntEnable(INT_TIMER0A);//NVIC
//    //使能TIMER0A
//    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
//    //TIMEOUT标志位触发中断
//    IntMasterEnable();
//    //master interrupt enable API for all interrupts
//    TimerEnable(TIMER1_BASE, TIMER_A);
//    //TIMER0A开始计数，当计数值等于TimerLoadSet，触发中断
//}
//void Timer1IntHandler(void)
//{
//
//    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
//    //清除标志位
//
//    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);//执行脉冲来控制转速
//
//}
