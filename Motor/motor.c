/**
  ******************************************************************************
  * 文件名程: Motor.c
  * 作    者: By Sw Young
  * 版    本: V1.0
  * 功    能:
  * 编写日期: 2018.3.29
  ******************************************************************************
  * 说明：
  * 硬件平台：
  *   MCUc:TM4C123、2相四线步进电机、DRV8825电机驱动、WiFi
  * 软件设计说明：
  *   通过无线精确控制小车的前进、后退距离；左转右转角度。
  * Github：
  ******************************************************************************
**/
#include <Motor/motor.h>
/**
  * 函 数 名:MotorInit.c
  * 函数功能: 电机初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明:
  * 接口说明：
  *     D1：Motor0 使能
  *     D2：Motor1 使能
  *     C4：Motor0 方向
  *     C5：Motor0 速度
  *     C6：Motor1 速度
  *     C7：Motor1 方向
  *   By Sw Young
  *   2018.03.29
  */

void MotorInit(void)
{
    //方向控制引脚：C4、C7  高电平为正转
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    //输出GPIO配置
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_5|GPIO_PIN_6);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4); //默认正转
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);

    //速度控制引脚：C5、C6
    //输出GPIO配置                  32细分下 推荐10K——26K
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);

    //使能控制引脚：D0、D1   低电平使能
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    //输出GPIO配置
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_1|GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1); //默认不使能
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);

}

/**
  * 函 数 名:MotorSet
  * 函数功能: 电机控制
  * 输入参数: uint8_t Motor,uint8_t Motor0Direction,uint8_t Motor1Direction
  * 返 回 值: 无
  * 说    明:
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
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);       //低电平使能
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
    }
    else if(Motor==1)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);       //低电平使能
    }
    else if(Motor==2)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);       //低电平使能
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);       //低电平使能
    }
    else if(Motor==3)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
    }

    if(Motor0Direction==0)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4); //高电平正转
    }
    else if (Motor0Direction==1)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);           //低电平反转
    }

    if(Motor1Direction==0)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7); //高电平正转
    }
    else if (Motor1Direction==1)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);           //低电平反转
    }
}
