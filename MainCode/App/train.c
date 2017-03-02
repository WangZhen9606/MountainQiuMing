 /*!
  * @file       servo.c
  * @brief      ����ͷ˫�����򣺵��ģ��
  * @author     Zhen
  * @version    v1.0
  * @date       2017-01-18
  */

#include "common.h"
#include "include.h"

/*!
 *  @brief      �������
 *  @since      v5.0
 *  @note       ʹ��FTM0��ͨ��0������PTC1������������"train.h"
 */

/*****************�����ʼ��********************/
void train_init(void)
{
 ftm_pwm_init(Train_FTM, Right_CH,Train_HZ,5000);      //��ʼ�� ��� PWM     //��ʼ�� �ұߵ����ͨ��0��PTA8��  PWM
 ftm_pwm_init(Train_FTM, Left_CH,Train_HZ,5000);      //��ʼ�� ��ߵ����ͨ��1��PTA9��  PWM
 
}
/*****************��� �ٶ�********************/               //aΪ���ռ�ձ�
uint32 train_speed_to_duty(float a)
{
  float tmp;
  
  tmp = 5000.0-a*50;                 
  
  return (uint32)tmp;
}
/********************����********************/
void Speed_Change(float speedL,float speedR)
{
  ftm_pwm_duty(Train_FTM,Left_CH, Train_Speed(speedL));
  ftm_pwm_duty(Train_FTM,Right_CH,Train_Speed(speedR));
}