/*
 * mpu6050_firRefi.h
 *
 *  Created on: 2016年7月6日
 *      Author: lenovo
 */

#ifndef HARDWARE_MPU6050_MPU6050_FIRREFI_H_
#define HARDWARE_MPU6050_MPU6050_FIRREFI_H_

/*=====标准库头文件 =============*/
#include <stdint.h>
#include <stdbool.h>

#define u8		uint8_t
#define u16		uint16_t

extern u8 MPU_Write_Byte(u8 reg,u8 data);
extern u8 MPU_Read_Byte(u8 reg);
extern u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf);
extern u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf);



#endif /* HARDWARE_MPU6050_MPU6050_FIRREFI_H_ */
