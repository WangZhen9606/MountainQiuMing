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

uint8 imgbuff[CAMERA_SIZE];    //定义存储接收图像的数组
uint8 img[CAMERA_H][CAMERA_W];
    
//函数声明
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT0_IRQHandler(void);
void PIT1_IRQHandler(void);

    
void main()
{   
    
    servo_init();
    train_init();
    encoder_init();
    pit_init_ms(PIT0, 500);                                 //初始化PIT0，定时时间为： 1000ms
    pit_init_ms(PIT1, 20);
    eye_init(imgbuff);
    
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //图像大小
    Size_t size;                   //显示区域图像大小
    Site_t photo    = {0,0};
    Size_t RealImg  = {LCD_H, LCD_W};

    size.W = 240;//LCD_H
    size.H = 180;//LCD_W
    
    
    //配置中断服务函数
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置 PORTA 的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置 DMA0 的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //设置PIT0的中断服务函数为 PIT0_IRQHandler
    set_vector_handler(PIT1_VECTORn ,PIT1_IRQHandler);
    enable_irq (PIT0_IRQn);
    enable_irq (PIT1_IRQn);
    
    /************************ 配置 K60 的优先级  ***********************/
    //K60 的默认优先级 都为 0
    //参考帖子：急求中断嵌套的例程 - 智能车讨论区 - 山外论坛
    //          http://www.vcan123.com/forum.php?mod=viewthread&tid=499&page=1#pid3270
    
    NVIC_SetPriorityGrouping(4);            //设置优先级分组,4bit 抢占优先级,没有亚优先级

    NVIC_SetPriority(PORTA_IRQn,0);         //配置优先级     摄像头
    NVIC_SetPriority(PIT1_IRQn,2);         //配置优先级     变速
    NVIC_SetPriority(PORTE_IRQn,1);         //配置优先级     无线模块
    NVIC_SetPriority(DMA0_IRQn,2);          //配置优先级     摄像头DMA
    NVIC_SetPriority(PIT0_IRQn,3);          //配置优先级     正交解码  
    
    
   while(1){
     
    camera_get_img();                                   //摄像头获取图像
                      //黑白摄像头
    LCD_Img_Binary_Z(photo, size, imgbuff, imgsize);

    /******************** 山外多功能调试助手 【黑白模式】 发送图像到上位机 ***********************/
    //vcan_sendimg(imgbuff, sizeof(imgbuff));
    img_extract((uint8 *)img,(uint8 *)imgbuff, CAMERA_SIZE);
    /*******提取中线******/
    Deal();
    /******************/
  
   }

}
/*!
 *  @brief      PIT0中断服务函数
 *  @since      v5.0
 */
void PIT0_IRQHandler(void)
{
    int16 val1,val2;
    val1 = ftm_quad_get(FTM1);          //获取FTM 正交解码 的脉冲数(负数表示反方向)
    val2 = ftm_quad_get(FTM2);  
    ftm_quad_clean(FTM1);
    ftm_quad_clean(FTM2);

    if(val1>=0)
    {
        //printf("\n正转：\n左电机%d；右电机%d",val1,val2);
    }
    else
    {
        //printf("\n反转：\n左电机%d；右电机%d",val1,val2);
    }

    PIT_Flag_Clear(PIT0);       //清中断标志位
}

void PIT1_IRQHandler(void)
{
    Speed_Change(10,10);
    PIT_Flag_Clear(PIT1);
}


/*!
 *  @brief      PORTA中断服务函数
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
    
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif


}

/*!
 *  @brief      DMA0中断服务函数
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}

  /**
    BJ_init();
    while(1)
    {
        Forward_Turn();
        DELAY_MS(50);
    }
   **/
/**
void BJ_init(void)
{
   gpio_init(PTB20,GPO,0); //A
   gpio_init(PTB21,GPO,0); //A-
   gpio_init(PTB23,GPO,0); //B
   gpio_init(PTB24,GPO,0); //B-
   gpio_init(PTC16,GPO,1); //EN1
   gpio_init(PTC19,GPO,1); //EN2
   
}

void Forward_Turn(void)
{
    gpio_set(PTB23,0);
    gpio_set(PTB20,1); //A
    DELAY_MS(50);
    
    gpio_set(PTB20,0);
    gpio_set(PTB23,1); //B
    DELAY_MS(50);
   
    gpio_set(PTB23,0);
    gpio_set(PTB21,1); //A-
    DELAY_MS(50);
    
    gpio_set(PTB21,0);
    gpio_set(PTB24,1); //B-
    DELAY_MS(50);
   
}
**/