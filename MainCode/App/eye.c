 /*!
  * @file       eye.c
  * @brief      摄像头双车程序：图像处理模块
  * @author     Zhen
  * @version    v1.0
  * @date       2017-02-19
  */

#include "common.h"
#include "include.h"

/*!
 *  @brief      LCD与camera初始化
 *  @since      v1.0
 *  @note      
 */
void eye_init(uint8 *img)
{
    uint8 *imgbuff = (uint8*)img;
    LCD_init();
    camera_init(imgbuff);
}

/*!
 *  @brief      缩放原始图片上某点至LCD，倍数由图像放大倍数决定
 *  @since      v1.0
 *  @note       point:为原始图像上需放大的点的坐标;size:显示大小;imgsize:图像大小；
 */
void LCD_point_Z(Site_t point,Size_t size,Size_t imgsize,uint16 rgb565)
{
    uint16 x,y;
    uint8 X,Y;
    uint8 Htimes,Wtimes;        //高、宽的放大倍数
    Site_t draw;                //要打印的点的坐标
    Y = point.y+1;
    X = point.x+1;
    Htimes = size.H/imgsize.H;
    Wtimes = size.W/imgsize.W;
    
    for(y = point.y*Htimes;y<Y*Htimes;y++)
    {
        for(x = point.x*Wtimes;x<X*Wtimes;x++)
        {
          draw.x = x;
          draw.y = y;
          LCD_point(draw,rgb565);
        }
    }
}