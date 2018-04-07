/*
 * I2C.c
 *
 *  Created on: 2016��7��9��
 *      Author: lenovo
 */

#include "I2C.h"
#include "Hardware/Sys/sys.h"


//��ʼ��IIC
void IIC_Init(void){

	//ʹ�ܸ��˿�
	// * GPIO_PA2__ -> SDA
	// * GPIO_PA3__ -> SCL
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	SCL_OUT();
	SDA_OUT();

	IIC_SCL_H();
	IIC_SDA_H();
}


//����IIC��ʼ�ź�
void IIC_Start(void){

	SDA_OUT();     //sda�����
	IIC_SDA_H();	I2C_Delay();
	IIC_SCL_H();	I2C_Delay();

 	IIC_SDA_L();	I2C_Delay();//START:when CLK is high,DATA change form high to low
	IIC_SCL_L();	I2C_Delay();//ǯסI2C���ߣ�׼�����ͻ��������

}


//����IICֹͣ�ź�
void IIC_Stop(void){

	SDA_OUT();//sda�����
	IIC_SCL_L();	I2C_Delay();
	IIC_SDA_L();//STOP:when CLK is high DATA change form low to high
	I2C_Delay();

	IIC_SCL_H();	I2C_Delay();
	IIC_SDA_H();	I2C_Delay();//����I2C���߽����ź�
}


/* �ȴ�Ӧ���źŵ���
 * ����ֵ��1������Ӧ��ʧ��
 *        0������Ӧ��ɹ�
*/
uint8_t IIC_Wait_Ack(void){
	uint8_t ucErrTime=0;

	IIC_SDA_H();	I2C_Delay();

	SDA_IN();      //SDA����Ϊ����
	IIC_SCL_H();	I2C_Delay();

	while(READ_SDA){

		ucErrTime++;
		if(ucErrTime>250){

			IIC_Stop();
			return 1;
		}//end if
	}//end while

	IIC_SCL_L();//ʱ�����0
	return 0;
} //end func


//����ACKӦ��
void IIC_Ack(void){

	IIC_SCL_L();

	SDA_OUT();
	IIC_SDA_L();	I2C_Delay();
	IIC_SCL_H();	I2C_Delay();

	IIC_SCL_L();

	/*===����===*/
	SDA_IN();	//�ͷ�SDA����
}


//������ACKӦ��
void IIC_NAck(void)
{
	IIC_SCL_L();

	SDA_OUT();
	IIC_SDA_H();	I2C_Delay();
	IIC_SCL_H();	I2C_Delay();

	IIC_SCL_L();

	/*===����===*/
	SDA_IN();	//�ͷ�SDA����
}


//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC_Send_Byte(uint8_t txd){
	uint8_t t, bBit_W;

	SDA_OUT();
	IIC_SCL_L();//����ʱ�ӿ�ʼ���ݴ���

    for(t=0;t<8;t++){

        //IIC_SDA=(txd&0x80)>>7;
    	bBit_W = txd & 0x80;	//�Ӹ�λ��ʼ����
    	if(bBit_W)	IIC_SDA_H();
    	else IIC_SDA_L();

        txd<<=1;
        I2C_Delay();	//��TEA5767��������ʱ���Ǳ����
		IIC_SCL_H();	I2C_Delay();
		IIC_SCL_L();	I2C_Delay();
    }
}


//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t IIC_Read_Byte(uint8_t ack){
	uint8_t i,receive=0;

	_disable_interrupts();
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ ){

    	IIC_SCL_L();	I2C_Delay();
        IIC_SCL_H();

        receive<<=1;
        if(READ_SDA)	//receive++;
        	receive |= 0x01;
        else receive &= 0xfe;
        I2C_Delay();
    }
    if (!ack)	//0������
        IIC_NAck();//����nACK
    else		//1����
        IIC_Ack(); //����ACK

    _enable_interrupts();
    return receive;
}

















