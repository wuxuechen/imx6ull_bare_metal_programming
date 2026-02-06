#include "ledc.h"
#include "clock.h"

void delay(int msecond){
    for(int i=0; i<msecond*0x400; i++){}
}

int main(void){
    clock_init();
    init_io();
    init_led();
    delay(100);
    while(1){
        turn_off_led();
	delay(1000);
        turn_on_led();
	delay(1000);
    }
    return 0;
}
