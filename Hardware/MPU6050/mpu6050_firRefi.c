/*
 * mpu6050_firRefi.c
 *
 *  Created on: 2016��7��6��
 *      Author: lenovo
 */

#include "mpu6050_firRefi.h"
#include "mpu6050.h"
#include "Hardware/Sys/sys.h"

//#include "Hardware/LED/led.h"
#include "Hardware/I2C/I2C.h"

//IICдһ���ֽ�
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data){
    IIC_Start();

	IIC_Send_Byte(MPU_WRITE);//����������ַ+д����
//	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
//	{
//		IIC_Stop();
//		//���������Ƿ�Ӧ��
//		LED1_ON();
//
//		return 1;
//	}
	IIC_Wait_Ack();


    IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    IIC_Wait_Ack();		//�ȴ�Ӧ��

	IIC_Send_Byte(data);//��������
	if(IIC_Wait_Ack())	//�ȴ�ACK
	{
		IIC_Stop();
//		LED_R_ON();
		return 1;
	}

    IIC_Stop();
	return 0;
}


//IIC��һ���ֽ�
//reg:�Ĵ�����ַ
//����ֵ:����������
u8 MPU_Read_Byte(u8 reg){
	u8 res;

    IIC_Start();

	IIC_Send_Byte(MPU_WRITE);//����������ַ+д����
	IIC_Wait_Ack();		//�ȴ�Ӧ��

    IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    IIC_Wait_Ack();		//�ȴ�Ӧ��

    IIC_Start();
	IIC_Send_Byte(MPU_READ);//����������ַ+������
    IIC_Wait_Ack();		//�ȴ�Ӧ��

	res=IIC_Read_Byte(0);//��ȡ����,����nACK
    IIC_Stop();			//����һ��ֹͣ����

	return res;
}



//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf){
 	IIC_Start();

	IIC_Send_Byte((addr<<1)|0);//����������ַ+д����
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();
		return 1;
	}

    IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    IIC_Wait_Ack();		//�ȴ�Ӧ��

    IIC_Start();
	IIC_Send_Byte((addr<<1)|1);//����������ַ+������
    IIC_Wait_Ack();		//�ȴ�Ӧ��

	while(len){

		if(len==1)*buf=IIC_Read_Byte(0);//������,����nACK
		else *buf=IIC_Read_Byte(1);		//������,����ACK
		len--;
		buf++;
	}

    IIC_Stop();	//����һ��ֹͣ����
	return 0;
}



//IIC����д
//addr:������ַ
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i;
    IIC_Start();
	IIC_Send_Byte((addr<<1)|0);//����������ַ+д����
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();
		return 1;
	}
    IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    IIC_Wait_Ack();		//�ȴ�Ӧ��
	for(i=0;i<len;i++)
	{
		IIC_Send_Byte(buf[i]);	//��������
		if(IIC_Wait_Ack())		//�ȴ�ACK
		{
			IIC_Stop();
			return 1;
		}
	}
    IIC_Stop();
	return 0;
}













