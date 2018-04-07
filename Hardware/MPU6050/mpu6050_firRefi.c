/*
 * mpu6050_firRefi.c
 *
 *  Created on: 2016年7月6日
 *      Author: lenovo
 */

#include "mpu6050_firRefi.h"
#include "mpu6050.h"
#include "Hardware/Sys/sys.h"

//#include "Hardware/LED/led.h"
#include "Hardware/I2C/I2C.h"

//IIC写一个字节
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Byte(u8 reg,u8 data){
    IIC_Start();

	IIC_Send_Byte(MPU_WRITE);//发送器件地址+写命令
//	if(IIC_Wait_Ack())	//等待应答
//	{
//		IIC_Stop();
//		//测试器件是否应答
//		LED1_ON();
//
//		return 1;
//	}
	IIC_Wait_Ack();


    IIC_Send_Byte(reg);	//写寄存器地址
    IIC_Wait_Ack();		//等待应答

	IIC_Send_Byte(data);//发送数据
	if(IIC_Wait_Ack())	//等待ACK
	{
		IIC_Stop();
//		LED_R_ON();
		return 1;
	}

    IIC_Stop();
	return 0;
}


//IIC读一个字节
//reg:寄存器地址
//返回值:读到的数据
u8 MPU_Read_Byte(u8 reg){
	u8 res;

    IIC_Start();

	IIC_Send_Byte(MPU_WRITE);//发送器件地址+写命令
	IIC_Wait_Ack();		//等待应答

    IIC_Send_Byte(reg);	//写寄存器地址
    IIC_Wait_Ack();		//等待应答

    IIC_Start();
	IIC_Send_Byte(MPU_READ);//发送器件地址+读命令
    IIC_Wait_Ack();		//等待应答

	res=IIC_Read_Byte(0);//读取数据,发送nACK
    IIC_Stop();			//产生一个停止条件

	return res;
}



//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf){
 	IIC_Start();

	IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();
		return 1;
	}

    IIC_Send_Byte(reg);	//写寄存器地址
    IIC_Wait_Ack();		//等待应答

    IIC_Start();
	IIC_Send_Byte((addr<<1)|1);//发送器件地址+读命令
    IIC_Wait_Ack();		//等待应答

	while(len){

		if(len==1)*buf=IIC_Read_Byte(0);//读数据,发送nACK
		else *buf=IIC_Read_Byte(1);		//读数据,发送ACK
		len--;
		buf++;
	}

    IIC_Stop();	//产生一个停止条件
	return 0;
}



//IIC连续写
//addr:器件地址
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i;
    IIC_Start();
	IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();
		return 1;
	}
    IIC_Send_Byte(reg);	//写寄存器地址
    IIC_Wait_Ack();		//等待应答
	for(i=0;i<len;i++)
	{
		IIC_Send_Byte(buf[i]);	//发送数据
		if(IIC_Wait_Ack())		//等待ACK
		{
			IIC_Stop();
			return 1;
		}
	}
    IIC_Stop();
	return 0;
}













