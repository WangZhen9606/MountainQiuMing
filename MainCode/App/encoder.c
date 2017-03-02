 /*!
  * @file       encoder.c
  * @brief      ����ͷ˫�����򣺱���������ģ��
  * @author     Zhen
  * @version    v1.0
  * @date       2017-01-19
  */

#include "common.h"
#include "include.h"


/*!
 *  @brief      encoder��غ���
 *  @since      v5.0
 *  @note       FTM �������� ����
 */
void Lencoder_init(void)
{
    ftm_quad_init(FTM1);                                    //���������FTM1 ���������ʼ����A�ࣺPTA12 B�ࣺPTA13��
}

void Rencoder_init(void)
{
    ftm_quad_init(FTM2);                                    //�ұ�������FTM2 ���������ʼ����A�ࣺPTA10 B�ࣺPTA11��
}

void encoder_init(void)
{
    Lencoder_init();
    Rencoder_init();
}

