//
// Created by hp on 1/27/26.
//

#include "bsp_epittimer.h"

#include "bsp_int.h"
#include "ledc.h"

/*
 * @description		: 初始化EPIT定时器.
 *					  EPIT定时器是32位向下计数器,时钟源使用ipg=66Mhz
 * @param - frac	: 分频值，范围为0~4095，分别对应1~4096分频。
 * @param - value	: 倒计数值。
 * @return 			: 无
 */
void epit1_init(unsigned int frac, unsigned int value)
{
    if (frac > 0xffff)
        frac = 0xffff;
    EPIT1->CR = 0;
    /*
     * CR寄存器:
     * bit25:24 01 时钟源选择Peripheral clock=66MHz
     * bit15:4  frac 分频值
     * bit3:	1  当计数器到0的话从LR重新加载数值
     * bit2:	1  比较中断使能This bit enables the generation of interrupt on occurrence of compare event.
     * bit1:    1  初始计数值来源于LR寄存器值
     * bit0:    0  先关闭EPIT1
     */
    EPIT1->CR = (1 << 24 | frac << 4 | 1 << 3 | 1 << 2 | 1 << 1);
    EPIT1->LR = value /* 倒计数值 */;
    EPIT1->CMPR = 0; /* 比较寄存器，当计数器值和此寄存器值相等的话就会产生中断 */
    /* 使能GIC中对应的中断 			*/
    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn, (system_irq_handler_t)epit1_irqhandler, NULL);
    EPIT1->CR |= 1 << 0; /* 使能EPIT1 */
}

static int8_t state = -1;
/*
 * @description			: EPIT中断处理函数
 * @param				: 无
 * @return 				: 无
 */
void epit1_irqhandler(void)
{
    state *= -1;
    if (state > 0)
        turn_on_led();
    else
        turn_off_led();
    EPIT1->SR |= 1 << 0; /* 清除中断标志位 */
}
