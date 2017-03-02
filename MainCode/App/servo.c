 /*!
  *     COPYRIGHT NOTICE
  *     Copyright (c) 2013,山外科技
  *     All rights reserved.
  *     技术讨论：山外论坛 http://www.vcan123.com
  *
  *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
  *     修改内容时必须保留山外科技的版权声明。
  *
  * @file       main.c
  * @brief      山外K60 平台主程序
  * @author     山外科技
  * @version    v5.0
  * @date       2013-08-28
  */

#include "common.h"
#include "include.h"



/*!
 *  @brief      servo.h函数
 *  @since      v5.0
 *  @note       山外 S3010舵机 测试实验 ,山外 提供的 电机驱动模块，管脚都加入 MOS 管隔离，信号是反相的。
                例如常规的 高电平 使能
                舵机资料，请看如下链接：
                http://www.vcan123.com/forum.php?mod=collection&action=view&ctid=25
 */
/*****************舵机角度********************/
uint32 servo_angle_to_duty(int a)
{
  float tmp;
  
  tmp = 750.0+a*(1000.0/180.0);
  
  return (uint32)tmp;
}
/********************打角********************/
void Turn(int servo_angle)
{
  ftm_pwm_duty(S3010_FTM,S3010_CH, S3010_Angle(servo_angle));
}

/*************舵机初始化***************/
void servo_init(void)
{
    ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,S3010_Angle(0));      //初始化 舵机 PWM
}