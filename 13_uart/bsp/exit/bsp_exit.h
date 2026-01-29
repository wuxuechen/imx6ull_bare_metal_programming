//
// Created by hp on 1/26/26.
// 描述	   : 外部中断驱动头文件。
//

#ifndef INC_9_INT_BSP_EXIT_H
#define INC_9_INT_BSP_EXIT_H

#include "imx6ul.h"
/* 函数声明 */
extern volatile unsigned char key_flag;
void exit_init(void);
void gpio1_io18_irqhandler(void);

#endif //INC_9_INT_BSP_EXIT_H