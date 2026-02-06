#include "ledc.h"
#include "beep.h"
#include "bsp_ap3216.h"
#include "bsp_delay.h"
#include "bsp_exit.h"
#include "bsp_icm20608.h"
#include "bsp_int.h"
#include "bsp_keyfilter.h"
#include "bsp_rtc.h"
#include "bsp_uart.h"
#include "../bsp/lcd/bsp_lcd.h"
#include "../stdio/include/printf.h"
#include "../bsp/lcd/bsp_lcdapi.h"
#include "../stdio/include/vsprintf.h"
#include "bsp_rtc.h"
#include "../bsp/touchscreen/bsp_gt9147.h"

/**
 * @description	: 使能I.MX6U的硬件NEON和FPU
 * @param 		: 无
 * @return 		: 无
 */
void imx6ul_hardfpu_enable(void)
{
    uint32_t cpacr;
    uint32_t fpexc;

    /* 使能NEON和FPU */
    cpacr = __get_CPACR();
    cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk))
        | (3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
    __set_CPACR(cpacr);
    fpexc = __get_FPEXC();
    fpexc |= 0x40000000UL;
    __set_FPEXC(fpexc);
}


int main(void)
{
    int index = 0;
    int seconds2now = 0;
    imx6ul_hardfpu_enable(); /* 使能I.MX6U的硬件浮点 			*/
    int_init(); /* 初始化中断(一定要最先调用！) */
    init_io_led();
    init_io_beep();
    init_led();
    init_beep();
    filterkey_init();
    delay_init();
    uart_init();
    printf("%s\r\n", "booting...");
    ap3216c_init();
    lcd_init();
    icm20608_init();
    gt9147_init();
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
        icm20608_getdata();
        char axis[128] = {0};
        lcd_fillrect(200, 150, 700, 180,LCD_BLUE);
        sprintf(axis, "temperature:%d gx:%d,gy:%d,gz:%d ax:%d,ay:%d,az:%d", icm20608_dev.temp_act,
                icm20608_dev.gyro_x_act, icm20608_dev.gyro_y_act, icm20608_dev.gyro_z_act, icm20608_dev.accel_x_act,
                icm20608_dev.accel_y_act, icm20608_dev.accel_z_act);
        lcd_show_string(200, 160, 500, 16, 16, axis);
        unsigned short ir, ps, als;
        ap3216c_readdata(&ir, &ps, &als);
        // printf("ir:%d, ps:%d, als:%d\r\n", ir, ps, als);


        index++;
        if (index == 10)
            index = 0;
        delayms(100);
        switch_led();
    }
    return 0;
}
