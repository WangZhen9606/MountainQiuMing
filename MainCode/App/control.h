 /*!
  * @file       control.h
  * @brief      ����ͷ˫���������ݴ������ģ��
  * @author     Zhen
  * @version    v1.0
  * @date       2017-02-21
  */

#ifndef  _CONTROL_H
#define  _CONTROL_H

#define  To_Left   25  //����Ѱ�Һ������ ��ֵ ��Hֵ
#define  To_Right  Left_Black_Last+10  //����Ѱ�Һ������ ��ֵ
#define  End_Left   4  //����Ѱ�Һ����յ�
#define  End_Right 54  //����Ѱ�Һ���

extern uint8 imgbuff[CAMERA_SIZE];    //����洢����ͼ�������
extern uint8 img[CAMERA_H][CAMERA_W];

extern void Deal();
extern void Find_Midpoint();
extern uint8 Get_Left_Point();
extern uint8 Get_Right_point();

#endif