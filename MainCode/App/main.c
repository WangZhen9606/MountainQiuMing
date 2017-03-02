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

uint8 imgbuff[CAMERA_SIZE];    //����洢����ͼ�������
uint8 img[CAMERA_H][CAMERA_W];
    
//��������
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT0_IRQHandler(void);
void PIT1_IRQHandler(void);

    
void main()
{   
    
    servo_init();
    train_init();
    encoder_init();
    pit_init_ms(PIT0, 500);                                 //��ʼ��PIT0����ʱʱ��Ϊ�� 1000ms
    pit_init_ms(PIT1, 20);
    eye_init(imgbuff);
    
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //ͼ���С
    Size_t size;                   //��ʾ����ͼ���С
    Site_t photo    = {0,0};
    Size_t RealImg  = {LCD_H, LCD_W};

    size.W = 240;//LCD_H
    size.H = 180;//LCD_W
    
    
    //�����жϷ�����
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //���� PORTA ���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //���� DMA0 ���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϷ�����Ϊ PIT0_IRQHandler
    set_vector_handler(PIT1_VECTORn ,PIT1_IRQHandler);
    enable_irq (PIT0_IRQn);
    enable_irq (PIT1_IRQn);
    
    /************************ ���� K60 �����ȼ�  ***********************/
    //K60 ��Ĭ�����ȼ� ��Ϊ 0
    //�ο����ӣ������ж�Ƕ�׵����� - ���ܳ������� - ɽ����̳
    //          http://www.vcan123.com/forum.php?mod=viewthread&tid=499&page=1#pid3270
    
    NVIC_SetPriorityGrouping(4);            //�������ȼ�����,4bit ��ռ���ȼ�,û�������ȼ�

    NVIC_SetPriority(PORTA_IRQn,0);         //�������ȼ�     ����ͷ
    NVIC_SetPriority(PIT1_IRQn,2);         //�������ȼ�     ����
    NVIC_SetPriority(PORTE_IRQn,1);         //�������ȼ�     ����ģ��
    NVIC_SetPriority(DMA0_IRQn,2);          //�������ȼ�     ����ͷDMA
    NVIC_SetPriority(PIT0_IRQn,3);          //�������ȼ�     ��������  
    
    
   while(1){
     
    camera_get_img();                                   //����ͷ��ȡͼ��
                      //�ڰ�����ͷ
    LCD_Img_Binary_Z(photo, size, imgbuff, imgsize);

    /******************** ɽ��๦�ܵ������� ���ڰ�ģʽ�� ����ͼ����λ�� ***********************/
    //vcan_sendimg(imgbuff, sizeof(imgbuff));
    img_extract((uint8 *)img,(uint8 *)imgbuff, CAMERA_SIZE);
    /*******��ȡ����******/
    Deal();
    /******************/
  
   }

}
/*!
 *  @brief      PIT0�жϷ�����
 *  @since      v5.0
 */
void PIT0_IRQHandler(void)
{
    int16 val1,val2;
    val1 = ftm_quad_get(FTM1);          //��ȡFTM �������� ��������(������ʾ������)
    val2 = ftm_quad_get(FTM2);  
    ftm_quad_clean(FTM1);
    ftm_quad_clean(FTM2);

    if(val1>=0)
    {
        //printf("\n��ת��\n����%d���ҵ��%d",val1,val2);
    }
    else
    {
        //printf("\n��ת��\n����%d���ҵ��%d",val1,val2);
    }

    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}

void PIT1_IRQHandler(void)
{
    Speed_Change(10,10);
    PIT_Flag_Clear(PIT1);
}


/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
    
#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
    n = 28;
    if(flag & (1 << n))                                 //PTA28�����ж�
    {
        camera_href();
    }
#endif


}

/*!
 *  @brief      DMA0�жϷ�����
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