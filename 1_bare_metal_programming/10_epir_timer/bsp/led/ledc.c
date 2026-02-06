#include "ledc.h"

void init_io_led(){
    //IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 0x5;
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);
    //IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = 0x13008;
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);
}

void init_led(){
    GPIO1->GDIR |= (1<<3);
    GPIO1->DR &= ~(1<<3);
}

void turn_on_led(){
    GPIO1->DR &= ~(1<<3);
}

void turn_off_led(){
    GPIO1->DR |= (1<<3);
}


