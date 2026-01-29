//
// Created by hp on 1/28/26.
//

#include "bsp_uart.h"


/*
 * @description : 初始化串口1,波特率为115200
 * @param		: 无
 * @return		: 无
 */
void uart_init(void)
{
    /* 1、初始化串口IO 			*/
    uart_io_init();
    /* 2、初始化UART1  			*/
    uart_disable(UART1);	/* 先关闭UART1 		*/
    uart_softreset(UART1);	/* 软件复位UART1 		*/
    UART1->UCR1 =0;/* 先清除UCR1寄存器 */
    /*
     * 设置UART的UCR1寄存器，关闭自动波特率
     * bit14: 0 关闭自动波特率检测,我们自己设置波特率
     */
    UART1->UCR1 &= ~(1<<14);
    /*
     * 设置UART的UCR2寄存器，设置内容包括字长，停止位，校验模式，关闭RTS硬件流控
     * bit14: 1 忽略RTS引脚
     * bit8: 0 关闭奇偶校验
     * bit6: 0 1位停止位
      * bit5: 1 8位数据位
      * bit2: 1 打开发送
      * bit1: 1 打开接收
     */
    UART1->UCR2 |= (1<<14) | (1<<5) | (1<<2) | (1<<1);
    /*
     * UART1的UCR3寄存器
     * bit2: 1 必须设置为1！参考IMX6ULL参考手册3624页
     */
    UART1->UCR3 |= 1<<2;
    /*
         * 设置波特率
         * 波特率计算公式:Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1))
         * 如果要设置波特率为115200，那么可以使用如下参数:
         * Ref Freq = 80M 也就是寄存器UFCR的bit9:7=101, 表示1分频
         * UBMR = 3124
          * UBIR =  71
          * 因此波特率= 80000000/(16 * (3124+1)/(71+1))=80000000/(16 * 3125/72) = (80000000*72) / (16*3125) = 115200
         */
    UART1->UFCR = 5<<7; //ref freq等于ipg_clk/1=80Mhz
    UART1->UBIR = 71;
    UART1->UBMR = 3124;
    /* 使能串口 */
    uart_enable(UART1);
}

/*
 * @description : 初始化串口1所使用的IO引脚
 * @param		: 无
 * @return		: 无
 */
void uart_io_init(void)
{
    /* 1、初始化IO复用
 * UART1_RXD -> UART1_TX_DATA
 * UART1_TXD -> UART1_RX_DATA
 */
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);
    /* 2、配置UART1_TX_DATA、UART1_RX_DATA的IO属性
     *bit 16:0 HYS关闭
     *bit [15:14]: 00 默认100K下拉
     *bit [13]: 0 keeper功能
     *bit [12]: 1 pull/keeper使能
     *bit [11]: 0 关闭开路输出
     *bit [7:6]: 10 速度100Mhz
     *bit [5:3]: 110 驱动能力R0/6
     *bit [0]: 0 低转换率
     */
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10B0);
}

/*
 * @description : 关闭指定的UART
 * @param - base: 要关闭的UART
 * @return		: 无
 */
void uart_disable(UART_Type* base)
{
    base->UCR1 &= ~(1 << 0);
}

/*
 * @description : 打开指定的UART
 * @param - base: 要打开的UART
 * @return		: 无
 */
void uart_enable(UART_Type* base)
{
    base->UCR1 |= (1 << 0);
}

/*
 * @description : 复位指定的UART
 * @param - base: 要复位的UART
 * @return		: 无
 */
void uart_softreset(UART_Type* base)
{
    base->UCR2 &= ~(1 << 0); /* UCR2的bit0为0，复位UART  	  	*/
    while ((base->UCR2 & 0x1) == 0); /* 等待复位完成 					*/
}

void uart_setbaudrate(UART_Type* base, uint32_t baudrate)
{
}

/*
 * @description : 发送一个字符
 * @param - c	: 要发送的字符
 * @return		: 无
 */
void putc(unsigned char c)
{
    while (((UART1->USR2 >> 3) & 0X01) == 0); /* 等待上一次发送完成 */
    UART1->UTXD = c & 0xff;
}

/*
 * @description : 发送一个字符串
 * @param - str	: 要发送的字符串
 * @return		: 无
 */
void puts(char* s)
{
    char *p = s;

    while(*p)
        putc(*p++);
}

/*
 * @description : 接收一个字符
 * @param 		: 无
 * @return		: 接收到的字符
 */
unsigned char getc(void)
{
    while((UART1->USR2 & 0x1) == 0);/* 等待接收完成 */
    return UART1->URXD;/* 返回接收到的数据 */
}
void raise(int sig_nr)
{

}
