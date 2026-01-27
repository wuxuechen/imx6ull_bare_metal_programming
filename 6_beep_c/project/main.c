#include "ledc.h"
#include "beep.h"


void delay(int msecond){
    for(int i=0; i<msecond*0x400; i++){}
}

int main(void){
    init_io_led();
    init_io_beep();
    init_led();
    init_beep();
    delay(500);
    while(1){
        turn_off_led();
	switch_beep();
	delay(500);
        turn_on_led();
	switch_beep();
	delay(500);
    }
    return 0;
}
