 /*!
  * @file       encoder.c
  * @brief      摄像头双车程序：编码器测速模块
  * @author     Zhen
  * @version    v1.0
  * @date       2017-01-19
  */

#include "common.h"
#include "include.h"


/*!
 *  @brief      encoder相关函数
 *  @since      v5.0
 *  @note       FTM 正交解码 测试
 */
void Lencoder_init(void)
{
    ftm_quad_init(FTM1);                                    //左编码器：FTM1 正交解码初始化（A相：PTA12 B相：PTA13）
}

void Rencoder_init(void)
{
    ftm_quad_init(FTM2);                                    //右编码器：FTM2 正交解码初始化（A相：PTA10 B相：PTA11）
}

void encoder_init(void)
{
    Lencoder_init();
    Rencoder_init();
}

