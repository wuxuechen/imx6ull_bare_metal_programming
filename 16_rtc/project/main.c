#include "ledc.h"
#include "beep.h"
#include "bsp_delay.h"
#include "bsp_exit.h"
#include "bsp_int.h"
#include "bsp_keyfilter.h"
#include "bsp_rtc.h"
#include "bsp_uart.h"
#include "../bsp/lcd/bsp_lcd.h"
#include "../stdio/include/printf.h"
#include "../bsp/lcd/bsp_lcdapi.h"
#include "../stdio/include/vsprintf.h"
#include "bsp_rtc.h"


int main(void)
{
    int index = 0;
    int seconds2now = 0;
    int_init(); /* 初始化中断(一定要最先调用！) */
    init_io_led();
    init_io_beep();
    init_led();
    init_beep();
    filterkey_init();
    delay_init();
    uart_init();
    printf("%s\r\n", "booting...");
    lcd_init();
    rtc_enable();
    seconds2now = rtc_getseconds();
    printf("seconds to now: %d\n", seconds2now);

    for (int i = 0; i < 100; i++)
    {
        lcd_drawpoint(i, i,LCD_RED);
    }

    lcd_fillrect(100, 100, 150, 150,LCD_BLUE);
    delay(3);
    lcd_clear(LCD_BLUE);
    while (1)
    {
        tftlcd_dev.backcolor = LCD_BLUE;
        tftlcd_dev.forecolor = LCD_BLACK;
        delayms(1);
        lcd_show_string(200, 40, 260, 32, 32, (char*)"ALPHA IMX6U");
        char info[64] = {0};
        sprintf(info, "RGBLCD:%d!!!", index);
        lcd_show_string(200, 80, 240, 24, 24, info);
        lcd_show_string(200, 110, 240, 16, 16, (char*)"autumn");
        struct rtc_datetime datetime;
        rtc_getdatetime(&datetime);
        char time[64] = {0};
        sprintf(time, "Time:%d/%d/%d %d-%d-%d", datetime.year, datetime.month, datetime.day,
                        datetime.hour, datetime.minute, datetime.second);
        lcd_show_string(200, 130, 240, 12, 12, time);
        index++;
        if (index == 10)
            index = 0;
        delayms(200);
        switch_led();
    }
    return 0;
}
