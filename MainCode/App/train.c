 /*!
  * @file       servo.c
  * @brief      摄像头双车程序：电机模块
  * @author     Zhen
  * @version    v1.0
  * @date       2017-01-18
  */

#include "common.h"
#include "include.h"

/*!
 *  @brief      舵机函数
 *  @since      v5.0
 *  @note       使用FTM0，通道0，引脚PTC1，变量定义在"train.h"
 */

/*****************电机初始化********************/
void train_init(void)
{
 ftm_pwm_init(Train_FTM, Right_CH,Train_HZ,5000);      //初始化 舵机 PWM     //初始化 右边电机（通道0—PTA8）  PWM
 ftm_pwm_init(Train_FTM, Left_CH,Train_HZ,5000);      //初始化 左边电机（通道1—PTA9）  PWM
 
}
/*****************电机 速度********************/               //a为电机占空比
uint32 train_speed_to_duty(float a)
{
  float tmp;
  
  tmp = 5000.0-a*50;                 
  
  return (uint32)tmp;
}
/********************变速********************/
void Speed_Change(float speedL,float speedR)
{
  ftm_pwm_duty(Train_FTM,Left_CH, Train_Speed(speedL));
  ftm_pwm_duty(Train_FTM,Right_CH,Train_Speed(speedR));
}