#include "ledc.h"


void delay(int msecond){
    for(int i=0; i<msecond*0x400; i++){}
}

int main(void){
    init_io();
    init_led();
    delay(100);
    while(1){
        turn_off_led();
	delay(100);
        turn_on_led();
	delay(100);
    }
    return 0;
}
