 /*!
  * @file       control.c
  * @brief      摄像头双车程序：数据处理控制模块
  * @author     Zhen
  * @version    v1.0
  * @date       2017-02-21
  */
/////////////////////////////////////////////////////
//
//Tips:图像最上一行为0
//
////////////////////////////////////////////////////




#include "common.h"
#include "include.h"

/******************数据区*****************/
uint8  Typical_Row[52] = {   40,39,38,37,36,35,34,33,32,31,//59-i;(i从19~39)
                          46,45,44,43,42,41,40,39,38,37,
                          36,35,34,33,32,31,30,29,28,27,
                          26,25,24,23,22,21,20,19,18,17,
                          16,14,13,12,11,10, 9, 8, 7, 6, 5, 4};//行列举

int16   Half_Road[52] = {  32,32,32,31,31,31,30,30,30,29,29,
                           28,28,27,27,27,26,26,25,25,25,
                           24,24,23,23,22,22,21,21,20,20,
                           19,19,19,18,18,17,17,16,16,16,
                           15,15,14,14,13,13,13,13,12,12 ,11};
uint16  Left_Black[6] = {0,0,0,0,0,0},Left_Black_Last = 0;
uint16  Right_Black[6] = {0,0,0,0,0,0},Right_Black_Last = 79;
uint16  Centre[6] = {40,40,40,40,40,40};
Site_t  Printing = {0,0};
Site_t  NowRow = {20,50};
uint16  Average_Centre;
/****************************************/

float abs_flt(float i)//作用： 求绝对值  浮点型
{
     float A;
     A=i;
     if(A<0) return (-A);
     else    return A;
} 

int16 abs_int(int16 i)//作用： 求绝对值  int型
{
     int16 B;
      B=i;
     if(B<0) return (-B);
     else    return B;
} 

//寻找中线
void Find_Midpoint()
{
    uint8  j,i,k;//行列
    uint8  Effective_Row;
    uint16 sum = 0;
    Size_t imgsizeControl  = {CAMERA_W, CAMERA_H};             //图像大小
    Size_t RealImgControl = {240, 180};
    
    for(j=0;j<10;j++)
    {
          Effective_Row = Typical_Row[j]; //当前行         
          NowRow.y = Effective_Row;      //确定要寻找的行

        //由中心向左找左边线
          for(i=29;i>2;i--)                                     //中间向两边扫描
          {
            if(img[Effective_Row][i]==0&&img[Effective_Row][i-1]==1)
            {
          //从左边线向右寻找右边线
              for(k=i;k<79-2;k++)
              {
                  if(img[Effective_Row][k]==0&&img[Effective_Row][k+1]==1)
                  {
                      if(abs_int(k+1-(i+1))>10)
                      {       
                             Left_Black[j] = i-1  ;
                             Left_Black_Last = Left_Black[j];
                             Right_Black[j] = k+1 ;
                             Right_Black_Last = Right_Black[j];
                             break;
                      }   
                  }
               }
              break;
             }
           }  //一行找完
          //检查是非寻找到两侧黑边
          //if(Left_Black[j] == 0){
          //Left_Black[j] = Left_Black_Last;
          //}
          //if(Right_Black == 0){
          //Right_Black[j] = Right_Black_Last;
          //}
            //计算中线
          Centre[j] = (Left_Black[j]+Right_Black[j])/2;
          //显示部分
          Printing.y = Effective_Row;
          Printing.x = Left_Black[j];
          LCD_point_Z(Printing,RealImgControl,imgsizeControl,GREEN);

          Printing.x = Right_Black[j];
          LCD_point_Z(Printing,RealImgControl,imgsizeControl,GREEN);

          Printing.x = Centre[j];
          LCD_point_Z(Printing,RealImgControl,imgsizeControl,RED);

    }
    //从左至右扫描
    for(j = 0;j < 10;j++){
        sum += Centre[j];
    }
    Average_Centre = sum/10;
    
}

void AngleDeal()
{
    int16 ErrorSum = 0;
    int16 Error_Now,Error_Last;
    Error_Now = Average_Centre - 40;
    if(Error_Now > 0)//右转
      Turn(5);
    if(Error_Now < 0)//左转
      Turn(-5);
    if(Error_Now == 0)
      Turn(0);
}

void Deal()
{
    Find_Midpoint();
    AngleDeal();
}

uint8 Get_Left_Point()
{
    return Left_Black_Last;
}

uint8 Get_Right_point()
{
    return Right_Black_Last;
}