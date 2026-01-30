#include "bsp_delay.h"
#include "imx6ul.h"
#include "bsp_int.h"
#include "ledc.h"


void delay_init(void)
{
    GPT1->CR = 0;/* 清零，bit0也为0，即停止GPT  			*/
    GPT1->CR = 1 <<15;/* bit15置1进入软复位 				*/
    while((GPT1->CR >> 15) & 0x01);	/*等待复位完成 						*/
    /*
        * GPT的CR寄存器,GPT通用设置
        * bit22:20	000 输出比较1的输出功能关闭，也就是对应的引脚没反应
     * bit9:    0   Restart模式,当CNT等于OCR1的时候就产生中断
     * bit8:6   001 GPT时钟源选择ipg_clk=66Mhz
     * bit
       */
    GPT1->CR = (1<<6);
    // GPT1->CR = (1<<1)|(1<<6);

    /*
     * GPT的PR寄存器，GPT的分频设置
     * bit11:0  设置分频值，设置为0表示1分频，
     *          以此类推，最大可以设置为0XFFF，也就是最大4096分频
     */
    GPT1->PR = 65;	/* 设置为65，即66分频，因此GPT1时钟为66M/(65+1)=1MHz */
    /*
      * GPT的OCR1寄存器，GPT的输出比较1比较计数值，
      *	GPT的时钟为1Mz，那么计数器每计一个值就是就是1us。
      * 为了实现较大的计数，我们将比较值设置为最大的0XFFFFFFFF,
      * 这样一次计满就是：0XFFFFFFFFus = 4294967296us = 4295s = 71.5min
      * 也就是说一次计满最多71.5分钟，存在溢出
      */
    GPT1->OCR[0] = 0XFFFFFFFF;
    // GPT1->OCR[0] = 500000;
    // GPT1->IR = 1<<0;

    /*
     * 使能GIC里面相应的中断，并且注册中断处理函数
     */
    // GIC_EnableIRQ(GPT1_IRQn);	//使能GIC中对应的中断
    // system_register_irqhandler(GPT1_IRQn, (system_irq_handler_t)gpt1_irqhandler, NULL);	//注册中断服务函数
    GPT1->CR |= 1<<0;			//使能GPT1
}

void gpt1_irqhandler(void)
{
    /*
     * GPT的SR寄存器，状态寄存器
     * bit2： 1 输出比较1发生中断
     */
    if(GPT1->SR & (1<<0))
    {
        switch_led();
    }

    GPT1->SR |= 1<<0; /* 清除中断标志位 */
}
/*
 * @description		: 微秒(us)级延时
 * @param - value	: 需要延时的us数,最大延时0XFFFFFFFFus
 * @return 			: 无
 */
void delayus(volatile unsigned int n)
{
    unsigned long oldcnt,newcnt;
    unsigned long tcntvalue = 0;	/* 走过的总时间  */

    oldcnt = GPT1->CNT;
    while (1)
    {
        newcnt = GPT1->CNT;
        if (newcnt!=oldcnt)
        {
            if (newcnt>oldcnt)
            {
                tcntvalue += newcnt-oldcnt;
            }else
            {
                tcntvalue+=newcnt-oldcnt+0XFFFFFFFF;
            }
            oldcnt = newcnt;
            if (tcntvalue>n)
                break;
        }
    }
}
void delayms(volatile unsigned int n)
{
    int i = 0;
    for(i=0; i<n; i++)
    {
        delayus(1000);
    }
}
void delay(volatile unsigned int n)
{
    int i = 0;
    for(i=0; i<n; i++)
    {
        delayms(1000);
    }
}
