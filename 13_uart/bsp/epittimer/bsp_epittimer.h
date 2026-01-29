//
// Created by hp on 1/27/26.
// 描述	   : EPIT定时器驱动头文件
//

#ifndef INC_10_EPIR_TIMER_BSP_EPITTIMER_H
#define INC_10_EPIR_TIMER_BSP_EPITTIMER_H
#include "imx6ul.h"

/* 函数声明 */
void epit1_init(unsigned int frac, unsigned int value);
void epit1_irqhandler(void);

#endif //INC_10_EPIR_TIMER_BSP_EPITTIMER_H