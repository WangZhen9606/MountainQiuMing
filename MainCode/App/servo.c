 /*!
  *     COPYRIGHT NOTICE
  *     Copyright (c) 2013,ɽ��Ƽ�
  *     All rights reserved.
  *     �������ۣ�ɽ����̳ http://www.vcan123.com
  *
  *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
  *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
  *
  * @file       main.c
  * @brief      ɽ��K60 ƽ̨������
  * @author     ɽ��Ƽ�
  * @version    v5.0
  * @date       2013-08-28
  */

#include "common.h"
#include "include.h"



/*!
 *  @brief      servo.h����
 *  @since      v5.0
 *  @note       ɽ�� S3010��� ����ʵ�� ,ɽ�� �ṩ�� �������ģ�飬�ܽŶ����� MOS �ܸ��룬�ź��Ƿ���ġ�
                ���糣��� �ߵ�ƽ ʹ��
                ������ϣ��뿴�������ӣ�
                http://www.vcan123.com/forum.php?mod=collection&action=view&ctid=25
 */
/*****************����Ƕ�********************/
uint32 servo_angle_to_duty(int a)
{
  float tmp;
  
  tmp = 750.0+a*(1000.0/180.0);
  
  return (uint32)tmp;
}
/********************���********************/
void Turn(int servo_angle)
{
  ftm_pwm_duty(S3010_FTM,S3010_CH, S3010_Angle(servo_angle));
}

/*************�����ʼ��***************/
void servo_init(void)
{
    ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,S3010_Angle(0));      //��ʼ�� ��� PWM
}