//
// Created by hp on 1/27/26.
// 描述	   : 定时器按键消抖驱动头文件。
//

#ifndef INC_11_KEY_FILTER_BSP_KEYFILTER_H
#define INC_11_KEY_FILTER_BSP_KEYFILTER_H

/* 函数声明 */

void filterkey_init(void);
void filtertimer_init(unsigned int value);
void filtertimer_stop(void);
void filtertimer_restart(unsigned int value);
void filtertimer_irqhandler(void);
void gpio1_16_31_irqhandler(void);

#endif //INC_11_KEY_FILTER_BSP_KEYFILTER_H