# Remote_Control_Car_PointRace_3_Car
## 实现效果
&emsp;&emsp;小车接收遥控器或电脑端的指令，完成指令动作
`

指令|功能
---|---
Fxxx|前进xxxcm
Bxxx|后退xxxcm
Rxxx|右转xxx°
Lxxx|左转xxx°
STOP|暂停任务
START|启动任务
Ax|参数修改
Px|参数修改
## 硬件连接
外设|MCU_IO
---|---
Motor0 使能|PD1
Motor1 使能|PD2
Motor0 方向|PC4
Motor1 方向|PC7
Motor0 速度|PC5
Motor1 速度|PC6
## 硬件结构
MCU：TM4C123G
电机：42步 步进电机
电机驱动：DRV8825电机驱动
无线：无线串口
姿态传感器：MPU6050
电池;2200mAh航模电池
