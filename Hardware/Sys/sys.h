/*
 * sys.h
 *
 *  Created on: 2016年7月9日
 *      Author: lenovo
 */

#ifndef HARDWARE_SYS_SYS_H_
#define HARDWARE_SYS_SYS_H_

/*=====标准库头文件 =============*/
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"


/*--- 根据定义的系统时钟具体决定“define” 使用那个时钟*/
//#define USE_Y2_16MHZ_DIV_5
//#define USE_Y2_16MHZ_DIV_4

///*---如果使用板载的Y2-16MHZ晶振，分频系数为5.将执行此部分代码---*/
//#ifdef USE_Y2_16MHZ_DIV_5
//#define I2C_Delay()		SysCtlDelay(26);	/*I2C专用延时. 2us延时 -> (2*40/3)*/
//
//#elif USE_Y2_16MHZ_DIV_4	/*分频系数为4*/
//#define I2C_Delay()		SysCtlDelay(33);	/*I2C专用延时. 2us延时 -> (2*50/3)*/
//
//#endif

#define I2C_Delay()		SysCtlDelay(13)	/*I2C专用延时. 2us延时 -> (2*40/3)*/




#define delay_ms(xms)	SysCtlDelay(xms*(SysCtlClockGet()/1000/3)) /*ms级延时*/























#endif /* HARDWARE_SYS_SYS_H_ */
