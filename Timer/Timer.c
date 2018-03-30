#include "timer.h"

extern uint8_t MotorOrderDirection;        //ǰ��0  ��1  ��2  �ң� 3
extern uint8_t MotorOrderDisplacement;     //ǰ���ʾ���룬���ұ�ʾת���
char Time_Flag = 0;
uint32_t Counter = 0;

//���������ʱ����Ч�������ԣ�����ʹ��һ����ʱ��ͨ���ı����ֵ�����������������
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
    //�����־λ
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
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);//ִ������������ת��
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);//ִ������������ת��
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);

    }
    else
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);//ִ������������ת��
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);//ִ������������ת��

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

    }
    IntMasterEnable();

}

//void Motor1_Contol(void)
//{
//    //ʹ��TIMER1
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
//    //TimerConfigure(TIMER1_BASE, TIMER_CFG_ONE_SHOT);//���μ���ģʽ
//    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);//�����Լ���ģʽ
//    TimerLoadSet(TIMER1_BASE, TIMER_A,SysCtlClockGet() / 10 - 1);//����Ƶ��10HZ
//    IntEnable(INT_TIMER0A);//NVIC
//    //ʹ��TIMER0A
//    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
//    //TIMEOUT��־λ�����ж�
//    IntMasterEnable();
//    //master interrupt enable API for all interrupts
//    TimerEnable(TIMER1_BASE, TIMER_A);
//    //TIMER0A��ʼ������������ֵ����TimerLoadSet�������ж�
//}
//void Timer1IntHandler(void)
//{
//
//    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
//    //�����־λ
//
//    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);//ִ������������ת��
//
//}
