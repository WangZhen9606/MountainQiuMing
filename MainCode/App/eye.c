 /*!
  * @file       eye.c
  * @brief      ����ͷ˫������ͼ����ģ��
  * @author     Zhen
  * @version    v1.0
  * @date       2017-02-19
  */

#include "common.h"
#include "include.h"

/*!
 *  @brief      LCD��camera��ʼ��
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
 *  @brief      ����ԭʼͼƬ��ĳ����LCD��������ͼ��Ŵ�������
 *  @since      v1.0
 *  @note       point:Ϊԭʼͼ������Ŵ�ĵ������;size:��ʾ��С;imgsize:ͼ���С��
 */
void LCD_point_Z(Site_t point,Size_t size,Size_t imgsize,uint16 rgb565)
{
    uint16 x,y;
    uint8 X,Y;
    uint8 Htimes,Wtimes;        //�ߡ���ķŴ���
    Site_t draw;                //Ҫ��ӡ�ĵ������
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