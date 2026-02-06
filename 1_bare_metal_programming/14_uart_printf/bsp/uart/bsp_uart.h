//
// Created by hp on 1/28/26.
// 串口驱动文件头文件。
//

#ifndef INC_13_UART_BSP_UART_H
#define INC_13_UART_BSP_UART_H
#include "imx6ul.h"


/* 函数声明 */
void uart_init(void);
void uart_io_init(void);
void uart_disable(UART_Type *base);
void uart_enable(UART_Type *base);
void uart_softreset(UART_Type *base);
void uart_setbaudrate(UART_Type *base, uint32_t baudrate);
void putc(unsigned char c);
void puts(char *s);
unsigned char getc(void);
void raise(int sig_nr);

#endif //INC_13_UART_BSP_UART_H