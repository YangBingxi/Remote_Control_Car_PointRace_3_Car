/**
  ******************************************************************************
  * �ļ�����: main.c
  * ��    ��: By Sw Young
  * ��    ��: V1.0
  * ��    ��:
  * ��д����: 2018.3.29
  ******************************************************************************
  * ˵����
  * Ӳ��ƽ̨��
  *   MCUc:TM4C123��2�����߲��������DRV8825���������WiFi
  * ������˵����
  *   ͨ�����߾�ȷ����С����ǰ�������˾��룻��ת��ת�Ƕȡ�
  * Github��
  ******************************************************************************
**/
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
#include "Hardware/I2C/I2C.h"
#include "Hardware/MPU6050/mpu6050.h"
#include "Hardware/MPU6050/mpu6050_firRefi.h"
#include "Hardware/DMP/inv_mpu.h"
#include "Hardware/DMP/inv_mpu_dmp_motion_driver.h"

extern uint32_t Counter;
extern uint8_t MotorOrderDirection;        //ǰ��0  ��1  ��2  �ң� 3
extern uint8_t MotorOrderDisplacement;     //ǰ���ʾ���룬���ұ�ʾת���
uint32_t CountBan = 65335;                 //Counter���ֵ65535������һȦ6400�ʣ���Ч����Ϊ10Ȧ����200cm
uint32_t SendCount = 0;                    //���ͼ�������
uint8_t FlagSend = 0;                      //���ͱ�־λ
uint8_t Time;                              //ʱ�����
uint8_t CharTable[10];                     //�ش�����
uint32_t CharNum;                          //��ʱ����
extern uint8_t Beep_Flag;                  //��������־λ
uint8_t Flag_Stop = 0;
extern uint32_t CountBan_tem;
extern uint8_t Swap;

/**
 * MPU6050���
 */
uint16_t tmp;                   //�¶�
short aacx,aacy,aacz;           //���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;        //������ԭʼ����
float pitch,roll,yaw;           //ŷ����

float parameter_Ang = 95.0;

/**
  * �� �� ��:main.c
  * ��������: ������
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ������
  *   By Sw Young
  *   2018.03.29
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

    //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

    Uart0Iint();
    Uart1Iint();
    MotorInit();
    MotorContolTimer();
    MotorSet(3,0,0);
    Beep_Configure();
    TimerDisable(TIMER1_BASE, TIMER_A);
//    MPU_Init();
//    while(mpu_dmp_init())
//    {//����while����ⲻ��MPU6050
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
//        delay_ms(1000);
//        //����mpu���󱨾�
//    }//������������
//    UARTprintf("mpu is ok!");
    //UARTprintf("TEST");   //UARTprint��������ض�����UART1

    while(1)
    {
        if(MotorOrderDirection==0)  //F
        {
           // Counter = 0; //��������
            MotorSet(2,0,1);
        }
        if(MotorOrderDirection==1)  //B
        {
           // Counter = 0; //��������
            MotorSet(2,1,0);
        }
        if(MotorOrderDirection==2)  //L
        {
           // Counter = 0; //��������
            MotorSet(1,0,1);
        }
        if(MotorOrderDirection==3)  //R
        {
           // Counter = 0; //��������
            MotorSet(0,0,1);
        }
        //���㹫ʽ��200��һת��һת20cm,32ϸ�֣�Distance = 20*Counter/(200*32)��
        if(MotorOrderDirection==0||MotorOrderDirection==1)
        {
            CountBan = MotorOrderDisplacement*10*32;
            //UARTprintf("Dis%d",(Counter*20)/6400);
        }
        //���㹫ʽ���־�16cm��1/4����Ϊ25.1327cm����Ӧ20cmΪ400�������1/4����Ϊ251����֪ÿʮ����27.888889��
        else if (MotorOrderDirection==2||MotorOrderDirection==3)
        {
//          CountBan = (int)MotorOrderDisplacement*2.788889*32;  //����ֵ89.3
            CountBan = (int)MotorOrderDisplacement*parameter_Ang;         //������90.2
            //UARTprintf("Ang%d",(int)(Counter/89.3));
        }

        if(Swap)
            CountBan = CountBan_tem;
        if(Counter>CountBan)
        {
            Counter = 0; //��������
            FlagSend = 0;
            MotorSet(3,0,0);//�ƶ�
            TimerDisable(TIMER0_BASE, TIMER_A);
            //TimerDisable(TIMER1_BASE, TIMER_A);
            Beep_Flag=0;

        }
        if(Flag_Stop)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
            delay_ms(200);
//            UARTprintf("Counter%d",Counter);
//            UARTprintf("CountBan%d",CountBan);
        }
        SendCount++;
        if(SendCount>1000)
        {
            SendCount = 0;
            if((MotorOrderDirection==0||MotorOrderDirection==1)&&FlagSend)
            {
//                UARTprintf("D%d",(Counter*20)/6400);
//                UARTprintf("T%d",Counter/10);
                //����λ��
                CharNum = (Counter*20)/6400+1;   //���޸�
                CharTable[0] = 'D';
                CharTable[1] = CharNum/100+48;
                CharTable[2] = CharNum/10%10+48;
                CharTable[3] = CharNum%10+48;
                CharTable[4] = '0';
                CharTable[5] = '0';
                UART1Send(CharTable,10);

                //����ʱ��
                CharNum = Counter/10;
                CharTable[0] = 'T';
                CharTable[1] = CharNum/10000+48;
                CharTable[2] = CharNum/1000%10+48;
                CharTable[3] = CharNum/100%10+48;
                CharTable[4] = CharNum/10%10+48;
                CharTable[5] = CharNum%10+48;
                UART1Send(CharTable,10);

//                OLED_ShowNum(28,3,(Counter*20)/6400,3,16);
//                OLED_ShowNum(98,3,(int)(Counter/10),3,16);
            }
            else if ((MotorOrderDirection==2||MotorOrderDirection==3)&&FlagSend)
            {
//                UARTprintf("A%d",(int)(Counter/89.3));
//                UARTprintf("T%d",Counter/10);
                //����λ��
                CharNum = (Counter/(int)parameter_Ang); //������
                CharTable[0] = 'A';
                CharTable[1] = CharNum/100+48;
                CharTable[2] = CharNum/10%10+48;
                CharTable[3] = CharNum%10+48;
                CharTable[4] = '0';
                CharTable[5] = '0';
                UART1Send(CharTable,10);

                //����ʱ��
                CharNum = Counter/10;
                CharTable[0] = 'T';
                CharTable[1] = CharNum/10000+48;
                CharTable[2] = CharNum/1000%10+48;
                CharTable[3] = CharNum/100%10+48;
                CharTable[4] = CharNum/10%10+48;
                CharTable[5] = CharNum%10+48;
                UART1Send(CharTable,10);

//                OLED_ShowNum(28,6,(int)(Counter/89.3),3,16);
//                OLED_ShowNum(98,3,(int)(Counter/10),3,16);
            }
            if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0){

                //temp=MPU_Get_Temperature();   //�õ��¶�ֵ
                MPU_Get_Accelerometer(&aacx,&aacy,&aacz);   //�õ����ٶȴ���������
                MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);    //�õ�����������
                if(1){UARTprintf("Pitch  %d  ", (int)pitch);}
                if(1){UARTprintf("Roll  %d  ", (int)roll);}
                if(1){UARTprintf("Yaw  %d\n", (int)yaw);}
            }//end if
        }

    }

  //  return 0;
}
