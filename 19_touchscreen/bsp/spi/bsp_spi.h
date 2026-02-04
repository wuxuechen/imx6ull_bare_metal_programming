//
// Created by hp on 2/3/26.
// 描述	   : SPI驱动头文件
//


#ifndef INC_18_SPI_BSP_SPI_H
#define INC_18_SPI_BSP_SPI_H
#include "imx6ul.h"
/*函数声明*/

void spi_init(ECSPI_Type *base);
unsigned char spich0_readwrite_byte(ECSPI_Type *base, unsigned char txdata);

#endif //INC_18_SPI_BSP_SPI_H