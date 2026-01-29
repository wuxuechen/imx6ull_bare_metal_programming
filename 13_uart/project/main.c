#include "ledc.h"
#include "beep.h"
#include "bsp_delay.h"
#include "bsp_exit.h"
#include "bsp_int.h"
#include "bsp_keyfilter.h"
#include "bsp_uart.h"

int main(void)
{
    unsigned char a=0;
    int_init(); /* 初始化中断(一定要最先调用！) */
    key_flag = 0;
    init_io_led();
    init_io_beep();
    init_led();
    init_beep();
    filterkey_init();
    delay_init();
    uart_init();

    while (1)
    {
        puts("pls input your char\r\n");
        a=getc();
        //显示输入的字符
        puts("the content you input is:");
        putc(a);
        puts("\r\n\r\n");
        delay(1);
        switch_led();
    }
    return 0;
}
