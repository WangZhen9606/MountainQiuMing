 /*!
  * @file       servo.h
  * @brief      摄像头双车程序：舵机模块
  * @author     Zhen
  * @version    v1.0
  * @date       2017-01-17
  */
#ifndef _SERVO_H_
#define _SERVO_H_

#define S3010_FTM   FTM0
#define S3010_CH    FTM_CH0             //PTC1
#define S3010_HZ    (50)                //50Hz
#define S3010_Angle(int)  servo_angle_to_duty(int)

extern float  angle;
extern void servo_init(void);  
extern uint32 servo_angle_to_duty(int a);
extern void Turn(int servo_angle);

#endif