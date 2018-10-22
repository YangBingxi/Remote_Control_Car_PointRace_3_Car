/**
  ******************************************************************************
  * �ļ�����: Motor.c
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
#include <Motor/motor.h>
/**
  * �� �� ��:MotorInit.c
  * ��������: �����ʼ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��:
  * �ӿ�˵����
  *     D1��Motor0 ʹ��
  *     D2��Motor1 ʹ��
  *     C4��Motor0 ����
  *     C5��Motor0 �ٶ�
  *     C6��Motor1 �ٶ�
  *     C7��Motor1 ����
  *   By Sw Young
  *   2018.03.29
  */

void MotorInit(void)
{
    //����������ţ�C4��C7  �ߵ�ƽΪ��ת
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    //���GPIO����
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_5|GPIO_PIN_6);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4); //Ĭ����ת
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);

    //�ٶȿ������ţ�C5��C6
    //���GPIO����                  32ϸ���� �Ƽ�10K����26K
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);

    //ʹ�ܿ������ţ�D0��D1   �͵�ƽʹ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //���GPIO����
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_1|GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1); //Ĭ�ϲ�ʹ��
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);

}

/**
  * �� �� ��:MotorSet
  * ��������: �������
  * �������: uint8_t Motor,uint8_t Motor0Direction,uint8_t Motor1Direction
  * �� �� ֵ: ��
  * ˵    ��:
  * Description:
  * Set Just Motor0 Please Set Parameter Motor As 0
  * Set Just Motor1 Please Set Parameter Motor As 1
  * Set Just Motor0 And Motor1 Please Set Parameter Motor As 2
  * Set Motor0Direction To Control Direction of Motor0 As Motor0Direction=0 Is Forward As Motor0Direction=1 Is Backward
  * Set Motor1Direction To Control Direction of Motor1 As Motor1Direction=0 Is Forward As Motor1Direction=1 Is Backward
  *
  *   By Sw Young
  *   2018.03.29
  */


void MotorSet(uint8_t Motor,uint8_t Motor0Direction,uint8_t Motor1Direction)
{
    if(Motor==0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);       //�͵�ƽʹ��
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
    }
    else if(Motor==1)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);       //�͵�ƽʹ��
    }
    else if(Motor==2)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);       //�͵�ƽʹ��
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);       //�͵�ƽʹ��
    }
    else if(Motor==3)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
    }

    if(Motor0Direction==0)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4); //�ߵ�ƽ��ת
    }
    else if (Motor0Direction==1)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);           //�͵�ƽ��ת
    }

    if(Motor1Direction==0)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7); //�ߵ�ƽ��ת
    }
    else if (Motor1Direction==1)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);           //�͵�ƽ��ת
    }
}
