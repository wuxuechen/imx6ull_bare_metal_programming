#include "main.h"

void init_io(){
    IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 0x5;
    IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = 0x13008;
}

void init_led(){
    GPIO1->GDIR = 0x8;
    GPIO1->DR = 0x0;
}

void turn_on_led(){
    GPIO1->DR &= ~(1<<3);
}

void turn_off_led(){
    GPIO1->DR |= (1<<3);
}

void delay(int msecond){
    for(int i=0; i<msecond*0x400; i++){}
}

int main(void){
    init_io();
        init_led();
    while(1){
        turn_off_led();
	delay(100);
        turn_on_led();
	delay(100);
    }
    return 0;
}
