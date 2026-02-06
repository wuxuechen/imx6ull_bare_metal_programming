#include "ledc.h"
#include "beep.h"
#include "keyc.h"


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
        int ret = read_key();
        if (ret) {	
            turn_off_led();
	    turn_off_beep();
	} else {
            turn_on_led();
	    turn_on_beep();
	}
        delay(10);
    }
    return 0;
}
