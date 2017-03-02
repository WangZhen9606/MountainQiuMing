 /*!
  * @file       control.h
  * @brief      摄像头双车程序：数据处理控制模块
  * @author     Zhen
  * @version    v1.0
  * @date       2017-02-21
  */

#ifndef  _CONTROL_H
#define  _CONTROL_H

#define  To_Left   25  //向左寻找黑线起点 列值 即H值
#define  To_Right  Left_Black_Last+10  //向右寻找黑线起点 列值
#define  End_Left   4  //向左寻找黑线终点
#define  End_Right 54  //向右寻找黑线

extern uint8 imgbuff[CAMERA_SIZE];    //定义存储接收图像的数组
extern uint8 img[CAMERA_H][CAMERA_W];

extern void Deal();
extern void Find_Midpoint();
extern uint8 Get_Left_Point();
extern uint8 Get_Right_point();

#endif