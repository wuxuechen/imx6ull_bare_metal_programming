#ifndef __MAIN_H
#define __MAIN_H
#define IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 (*(volatile unsigned int*) 0x020E0068)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 (*(volatile unsigned int*) 0x020E02F4)
#define GPIO1_BASE                  (0x0209C000)
typedef struct
{
	volatile unsigned int DR;							
	volatile unsigned int GDIR; 							
	volatile unsigned int PSR;								
	volatile unsigned int ICR1; 							
	volatile unsigned int ICR2; 							 
	volatile unsigned int IMR;								 
	volatile unsigned int ISR;			
	volatile unsigned int EDGE_SEL;  
} GPIO_Type;
#define GPIO1 ((GPIO_Type *)GPIO1_BASE)
#endif
