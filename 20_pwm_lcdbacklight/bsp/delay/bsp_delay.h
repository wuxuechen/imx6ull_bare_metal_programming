//
// Created by hp on 1/26/26.
//

#ifndef INC_9_INT_BSP_DELAY_H
#define INC_9_INT_BSP_DELAY_H
#include "imx6ul.h"


/* 函数声明 */
void delay_init(void);

void delayus(volatile unsigned int n);
void delayms(volatile unsigned int n);
void delay(volatile unsigned int n);
void gpt1_irqhandler(void);
#endif //INC_9_INT_BSP_DELAY_H