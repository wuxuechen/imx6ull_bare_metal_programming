#include "ledc.h"
#include "beep.h"
#include "bsp_delay.h"
#include "bsp_exit.h"
#include "bsp_int.h"
#include "bsp_keyfilter.h"
#include "bsp_uart.h"
#include "../bsp/lcd/bsp_lcd.h"
#include "../stdio/include/printf.h"
#include "../bsp/lcd/bsp_lcdapi.h"
#include "../stdio/include/vsprintf.h"

/* 背景颜色索引 */
unsigned int color[10] = {
    LCD_BLUE, LCD_GREEN, LCD_RED, LCD_CYAN, LCD_YELLOW,
    LCD_LIGHTBLUE, LCD_DARKBLUE, LCD_WHITE, LCD_BLACK, LCD_ORANGE

};

int main(void)
{
    int index = 0;
    int_init(); /* 初始化中断(一定要最先调用！) */
    key_flag = 0;
    init_io_led();
    init_io_beep();
    init_led();
    init_beep();
    filterkey_init();
    delay_init();
    uart_init();
    printf("%s\r\n", "booting...");
    lcd_init();
    for (int i = 0; i < 100; i++)
    {
        lcd_drawpoint(i, i,LCD_RED);
    }

    lcd_fillrect(100, 100, 150, 150,LCD_BLUE);
    delay(3);
    while (1)
    {
        lcd_clear(color[index]);
        tftlcd_dev.backcolor = color[index];
        tftlcd_dev.forecolor = index < 0 ? color[9] : color[index - 1];
        delayms(1);
        lcd_show_string(200, 40, 260, 32, 32, (char*)"ALPHA IMX6U");
        char info[64] = {0};
        sprintf(info, "RGBLCD:%d!!!", index);
        lcd_show_string(200, 80, 240, 24, 24, info);
        lcd_show_string(200, 110, 240, 16, 16, (char*)"autumn");
        lcd_show_string(200, 130, 240, 12, 12, (char*)"2026/01/29");
        index++;
        if (index == 10)
            index = 0;
        delayms(200);
        switch_led();
    }
    return 0;
}
