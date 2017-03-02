 /*!
  * @file       train.h
  * @brief      摄像头双车程序：电机模块
  * @author     Zhen
  * @version    v1.0
  * @date       2017-01-17
  */
#ifndef _TRAIN_H_
#define _TRAIN_H_

#define Train_FTM   FTM3                //FTM1（光电车） FTM3（摄像头）
#define Right_CH    FTM_CH1             //FTM1：PTA8     FTM3：CH0_PTE5
#define Left_CH     FTM_CH2             //FTM1：PTA9     FTM3：CH1_PTE6   CH2_PTE7
#define Train_HZ    (10000)                //10KHz
#define Train_Speed(float)  train_speed_to_duty(float)
extern float  Right_Speed;
extern float  Left_Speed;
/**********************************/
extern void train_init(void);
extern uint32 train_speed_to_duty(float a);
extern void Speed_Change(float speedL,float speedR);

#endif