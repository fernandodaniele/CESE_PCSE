/*
 * mcufriend.c
 *
 *  Created on: 16 oct. 2020
 *      Author: fernando
 */
#include "mcufriend.h"

#define TTRANS  20

void tftInit()
{
	spiWrite( SPI0, "1", 1);
	delay(TTRANS);
	spiWrite( SPI0, "\n", 1);
	delay(TTRANS);
}

void tftPrint(uint8_t* text, uint32_t bufferSize)
{
	spiWrite( SPI0, "2", 1);
	delay(TTRANS);
	spiWrite( SPI0, text, bufferSize);
	delay(TTRANS);
	spiWrite( SPI0, "\n", 1);
	delay(TTRANS);
}

void tftFillScreen(uint8_t* color) //uint16_t color
{
	spiWrite( SPI0, "3", 1);
	delay(TTRANS);
	spiWrite( SPI0,color, 5);
	delay(TTRANS);
	spiWrite( SPI0, "\n", 1);
	delay(TTRANS);
}

void tftSetCursor(uint8_t* x, uint8_t* y) //
{
	spiWrite( SPI0, "4", 1);
	delay(TTRANS);
	spiWrite( SPI0,x, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,y, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0, "\n", 1);
	delay(TTRANS);
}

void tftDrawRect(uint8_t* x, uint8_t* y, uint8_t* w, uint8_t* h, uint8_t* color)
{
	spiWrite( SPI0, "5", 1);
	delay(TTRANS);
	spiWrite( SPI0,x, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,y, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,w, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,h, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,color, 5);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0, "\n", 1);
	delay(TTRANS);
}

void tftSetTextColor(uint8_t* c)
{
	spiWrite( SPI0, "6", 1);
	delay(TTRANS);
	spiWrite( SPI0,c, 5);
	delay(TTRANS);
	spiWrite( SPI0, "\n", 1);
	delay(TTRANS);
}

void tftSetTextSize(uint8_t* s)  //de 1 a 9
{
	spiWrite( SPI0, "7", 1);
	delay(TTRANS);
	spiWrite( SPI0,s, 2);
	delay(TTRANS);
	spiWrite( SPI0, "\n", 1);
	delay(TTRANS);
}

void tftDrawLine(uint8_t* x0, uint8_t* y0, uint8_t* x1, uint8_t* y1, uint8_t* color)
{
	spiWrite( SPI0, "8", 1);
	delay(TTRANS);
	spiWrite( SPI0,x0, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,y0, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,x1, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,y1, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,color, 5);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0, "\n", 1);
	delay(TTRANS);
}

void tftDrawPixel(uint8_t* x, uint8_t* y, uint8_t* color)
{
	spiWrite( SPI0, "9", 1);
	delay(TTRANS);
	spiWrite( SPI0,x, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,y, 3);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0,color, 5);
	delay(TTRANS);
	spiWrite( SPI0,"-", 1);
	delay(TTRANS);
	spiWrite( SPI0, "\n", 1);
	delay(TTRANS);
}
