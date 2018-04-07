/*
 * I2C.h
 *
 *  Created on: 2016年7月9日
 *      Author: lenovo
 */

#ifndef HARDWARE_I2C_I2C_H_
#define HARDWARE_I2C_I2C_H_

/*=====标准库头文件 =============*/
#include <stdint.h>
#include <stdbool.h>

/*===== TivaWare 驱动库头文件====*/
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "inc/hw_memmap.h"



/*===设置输入输出===*/
#define SCL_OUT()	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_3)
#define SDA_OUT()	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_2)

#define SDA_IN()	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_2)

/*===设置高低电平====*/

#define IIC_SCL_H()	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,8)
#define IIC_SCL_L()	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0)

#define IIC_SDA_H()	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,4)
#define IIC_SDA_L()	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,0)

#define READ_SDA	GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_2)




//IIC所有操作函数
extern void IIC_Init(void);                //初始化IIC的IO口
extern void IIC_Start(void);				//发送IIC开始信号
extern void IIC_Stop(void);	  			//发送IIC停止信号
extern void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
extern uint8_t IIC_Read_Byte(uint8_t ack);//IIC读取一个字节
extern uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
extern void IIC_Ack(void);					//IIC发送ACK信号
extern void IIC_NAck(void);				//IIC不发送ACK信号

extern void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
extern uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);















#endif /* HARDWARE_I2C_I2C_H_ */
