#include "keyc.h"

void init_io_key(){
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0X1F080);
}

void init_key(){
    GPIO1->GDIR &= ~(1<<18);
    // GPIO1->DR &= ~(1<<3);
}

int read_key(){
    return (GPIO1->DR >> 18) & 1;    
}
