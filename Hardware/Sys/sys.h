/*
 * sys.h
 *
 *  Created on: 2016��7��9��
 *      Author: lenovo
 */

#ifndef HARDWARE_SYS_SYS_H_
#define HARDWARE_SYS_SYS_H_

/*=====��׼��ͷ�ļ� =============*/
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"


/*--- ���ݶ����ϵͳʱ�Ӿ��������define�� ʹ���Ǹ�ʱ��*/
//#define USE_Y2_16MHZ_DIV_5
//#define USE_Y2_16MHZ_DIV_4

///*---���ʹ�ð��ص�Y2-16MHZ���񣬷�Ƶϵ��Ϊ5.��ִ�д˲��ִ���---*/
//#ifdef USE_Y2_16MHZ_DIV_5
//#define I2C_Delay()		SysCtlDelay(26);	/*I2Cר����ʱ. 2us��ʱ -> (2*40/3)*/
//
//#elif USE_Y2_16MHZ_DIV_4	/*��Ƶϵ��Ϊ4*/
//#define I2C_Delay()		SysCtlDelay(33);	/*I2Cר����ʱ. 2us��ʱ -> (2*50/3)*/
//
//#endif

#define I2C_Delay()		SysCtlDelay(13)	/*I2Cר����ʱ. 2us��ʱ -> (2*40/3)*/




#define delay_ms(xms)	SysCtlDelay(xms*(SysCtlClockGet()/1000/3)) /*ms����ʱ*/























#endif /* HARDWARE_SYS_SYS_H_ */
