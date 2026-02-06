//
// Created by autumn on 1/16/26.
//

#include "clock.h"

static inline void dsb(void)
{
    __asm__ volatile ("dsb sy" ::: "memory");
}

static inline void isb(void)
{
    __asm__ volatile ("isb" ::: "memory");
}


void clock_init() {
    // Switch clock path if needed
    if (((CCM->CCSR >> 2) & 0x1) == 0) {
        CCM->CCSR &= ~(1U << 8);
        CCM->CCSR |= (1U << 2);
    }
    // Set PLL1 divider
    CCM_ANALOG->PLL_ARM = (1 << 13) | ((55 << 0) & 0x7f);
    // Divide ARM clock
    CCM->CACRR = 1U;
    //witch back
    CCM->CCSR &= ~(1U << 2);

    /*
    *   PLL2_PFD0 352MHz
        PLL2_PFD1 594MHz
        PLL2_PFD2 400MHz(实际为 396MHz)
        PLL2_PFD3 297MHz
        PLL3_PFD0 720MHz
        PLL3_PFD1 540MHz
        PLL3_PFD2 508.2MHz
        PLL3_PFD3 454.7MHz
     */

    // Set PFD of PPL2
    unsigned int reg = CCM_ANALOG->PFD_528;
    reg &= ~(0x3f3f3f3f);  // 528*18/PFD0_FRAC
    reg |= (32<<24); // 528*18/297
    reg |= (24<<26); // 528*18/396
    reg |= (16<<8); // 528*18/594
    reg |= (27<<0); // 528*18/352
    CCM_ANALOG->PFD_528=reg;

    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0x3f3f3f3f);
    reg |= (19<<24); // 480*18/454.7
    reg |= (17<<26); // 480*18/508.2
    reg |= (16<<8); // 480*18/540
    reg |= (12<<0); // 480*18/720
    CCM_ANALOG->PFD_480=reg;

    /*
        AHB_CLK_ROOT 132
        PERCLK_CLK_ROOT 66
        IPG_CLK_ROOT 66
     */
    // AHB_CLK_ROOT
    CCM->CBCMR &= ~(3U << 18);
    CCM->CBCMR |= (1 << 18);
    CCM->CBCDR &= ~(3U << 27);
    CCM->CBCDR &= ~(1 << 25);
    while (CCM->CDHIPR & (1<<5)){};

    // Divided into 3



    // CCM->CBCDR &= ~(7U << 10);
    // CCM->CBCDR |= (2 << 10);
    // while (CCM->CDHIPR & (1<<1)){};

    // /* Disable AHB clock output */
    // CCM->CCGR0 &= ~(3U << 10); // AHB clock gate (example bit position)
    // dsb();
    // isb();
    // CCM->CCGR0 |= (3U << 10); /* Enable AHB clock */


    // IPG_CLK_ROOT
    CCM->CBCDR &= ~(3U << 8);
    CCM->CBCDR |= (1 << 8);

    // PERCLK_CLK_ROOT
    CCM->CSCMR1 &= ~(1 << 6);
    CCM->CSCMR1 &= ~(127 << 0);


}
