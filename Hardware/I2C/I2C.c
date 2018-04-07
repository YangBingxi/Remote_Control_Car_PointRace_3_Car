/*
 * I2C.c
 *
 *  Created on: 2016年7月9日
 *      Author: lenovo
 */

#include "I2C.h"
#include "Hardware/Sys/sys.h"


//初始化IIC
void IIC_Init(void){

	//使能各端口
	// * GPIO_PA2__ -> SDA
	// * GPIO_PA3__ -> SCL
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	SCL_OUT();
	SDA_OUT();

	IIC_SCL_H();
	IIC_SDA_H();
}


//产生IIC起始信号
void IIC_Start(void){

	SDA_OUT();     //sda线输出
	IIC_SDA_H();	I2C_Delay();
	IIC_SCL_H();	I2C_Delay();

 	IIC_SDA_L();	I2C_Delay();//START:when CLK is high,DATA change form high to low
	IIC_SCL_L();	I2C_Delay();//钳住I2C总线，准备发送或接收数据

}


//产生IIC停止信号
void IIC_Stop(void){

	SDA_OUT();//sda线输出
	IIC_SCL_L();	I2C_Delay();
	IIC_SDA_L();//STOP:when CLK is high DATA change form low to high
	I2C_Delay();

	IIC_SCL_H();	I2C_Delay();
	IIC_SDA_H();	I2C_Delay();//发送I2C总线结束信号
}


/* 等待应答信号到来
 * 返回值：1，接收应答失败
 *        0，接收应答成功
*/
uint8_t IIC_Wait_Ack(void){
	uint8_t ucErrTime=0;

	IIC_SDA_H();	I2C_Delay();

	SDA_IN();      //SDA设置为输入
	IIC_SCL_H();	I2C_Delay();

	while(READ_SDA){

		ucErrTime++;
		if(ucErrTime>250){

			IIC_Stop();
			return 1;
		}//end if
	}//end while

	IIC_SCL_L();//时钟输出0
	return 0;
} //end func


//产生ACK应答
void IIC_Ack(void){

	IIC_SCL_L();

	SDA_OUT();
	IIC_SDA_L();	I2C_Delay();
	IIC_SCL_H();	I2C_Delay();

	IIC_SCL_L();

	/*===新增===*/
	SDA_IN();	//释放SDA总线
}


//不产生ACK应答
void IIC_NAck(void)
{
	IIC_SCL_L();

	SDA_OUT();
	IIC_SDA_H();	I2C_Delay();
	IIC_SCL_H();	I2C_Delay();

	IIC_SCL_L();

	/*===新增===*/
	SDA_IN();	//释放SDA总线
}


//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(uint8_t txd){
	uint8_t t, bBit_W;

	SDA_OUT();
	IIC_SCL_L();//拉低时钟开始数据传输

    for(t=0;t<8;t++){

        //IIC_SDA=(txd&0x80)>>7;
    	bBit_W = txd & 0x80;	//从高位开始发送
    	if(bBit_W)	IIC_SDA_H();
    	else IIC_SDA_L();

        txd<<=1;
        I2C_Delay();	//对TEA5767这三个延时都是必须的
		IIC_SCL_H();	I2C_Delay();
		IIC_SCL_L();	I2C_Delay();
    }
}


//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t IIC_Read_Byte(uint8_t ack){
	uint8_t i,receive=0;

	_disable_interrupts();
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ ){

    	IIC_SCL_L();	I2C_Delay();
        IIC_SCL_H();

        receive<<=1;
        if(READ_SDA)	//receive++;
        	receive |= 0x01;
        else receive &= 0xfe;
        I2C_Delay();
    }
    if (!ack)	//0不接收
        IIC_NAck();//发送nACK
    else		//1接收
        IIC_Ack(); //发送ACK

    _enable_interrupts();
    return receive;
}

















