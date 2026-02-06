#include "bsp_exit.h"

#include "../../imx6ul/core_ca7.h"
#include "../../imx6ul/fsl_iomuxc.h"
#include "../gpio/bsp_gpio.h"
#include "../int/bsp_int.h"
#include "../delay/bsp_delay.h"
#include "../beep/beep.h"

//
// Created by hp on 1/26/26.
//
/*
 * @description			: 初始化外部中断
 * @param				: 无
 * @return 				: 无
 */

volatile unsigned char key_flag = 0;

void exit_init(void)
{
    gpio_pin_config_t key_config;
    /* 1、设置IO复用 */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0); /* 复用为GPIO1_IO18 */
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0X1F080); /**/

    /* 2、初始化GPIO为中断模式 */
    key_config.direction = kGPIO_DigitalInput;
    key_config.interruptMode = kGPIO_IntFallingEdge;
    key_config.outputLogic = 0;
    gpio_init(GPIO1, 18, &key_config); /*GPIO1 控制器里的第 18 个 I/O*/

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    /* 使能GIC中对应的中断 18 包含在GPIO1_Combined_16_31_IRQn中，当 pin 18发生变化的时候，GPIO1_Combined_16_31_IRQn就能别触发，*/
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)gpio1_io18_irqhandler, NULL);
    gpio_clearintflags(GPIO1, 18);
    gpio_enableint(GPIO1, 18);
}

void gpio1_io18_irqhandler(void)
{
    key_flag = 1;                  // 设置标志，由主循环处理
    gpio_clearintflags(GPIO1, 18); // 先清标志
}
