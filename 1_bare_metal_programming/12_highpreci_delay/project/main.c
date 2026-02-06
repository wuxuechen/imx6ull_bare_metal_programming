#include "ledc.h"
#include "beep.h"
#include "bsp_delay.h"
#include "bsp_exit.h"
#include "bsp_int.h"
#include "bsp_keyfilter.h"

int main(void)
{
    int_init(); /* 初始化中断(一定要最先调用！) */
    key_flag = 0;
    init_io_led();
    init_io_beep();
    init_led();
    init_beep();
    filterkey_init();
    delay_init();

    while (1)
    {
        delay(1);
        switch_led();
    }
    return 0;
}
