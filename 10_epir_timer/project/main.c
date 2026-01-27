#include "ledc.h"
#include "beep.h"
#include "bsp_epittimer.h"
#include "bsp_exit.h"
#include "bsp_int.h"
#include "bsp_gpio.h"

int main(void)
{
    int_init(); /* 初始化中断(一定要最先调用！) */
    key_flag = 0;
    init_io_led();
    init_io_beep();
    init_led();
    init_beep();
    exit_init(); /* 初始化按键中断			*/
    epit1_init(0, 66000000/2);	/* 初始化EPIT1定时器，1分频
                             * 计数值为:66000000/2，也就是
                             * 定时周期为500ms。
                             */
    while (1)
    {
        if (key_flag)
        {
            key_flag = 0;
            turn_on_beep(); // 按下就响
            while (gpio_pinread(GPIO1, 18) == 0){}; // 等按键松开
            turn_off_beep(); // 松开停止
        }
    }
    return 0;
}
