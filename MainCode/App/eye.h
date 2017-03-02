 /*!
  * @file       eye.h
  * @brief      摄像头双车程序：图像处理模块
  * @author     Zhen
  * @version    v1.0
  * @date       2017-02-19
  */

#ifndef  _EYE_H
#define  _EYE_H

extern void LCD_point_Z(Site_t point,Size_t size,Size_t imgsize,uint16 rgb565);
extern void eye_init(uint8*img);
    
#endif