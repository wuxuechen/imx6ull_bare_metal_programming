#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

void init_io(){
    //IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 0x5;
    //*(volatile unsigned int*) 0x020E0068 = 0x5;
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);
    //IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = 0x13008;
    //*(volatile unsigned int*) 0x020E02F4 =  0x13008;
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X13008);
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

void delay(int msecond){
    for(int i=0; i<msecond*0x400; i++){}
}

int main(void){
    init_io();
    init_led();
    delay(200);
    while(1){
        turn_off_led();
	delay(100);
        turn_on_led();
	delay(100);
    }
    return 0;
}
