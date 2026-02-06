#include "beep.h"

void init_io_beep(){
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0X10B0);
}

void init_beep(){
    GPIO5->GDIR |= (1<<1);  // 输出
    GPIO5->DR |= (1<<1);    // 高电平关蜂鸣器
}

void switch_beep(){
    GPIO5->DR ^= (1<<1);
}

void turn_on_beep(){
    GPIO5->DR &= ~(1<<1);
}

void turn_off_beep(){
    GPIO5->DR |= (1<<1);
}

