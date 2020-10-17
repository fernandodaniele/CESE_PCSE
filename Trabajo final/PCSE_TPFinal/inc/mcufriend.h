/*
 * mcufriend.h
 *
 *  Created on: 16 oct. 2020
 *      Author: fernando
 */

#ifndef MISPROGRAMAS_PCSE_TPFINAL_INC_MCUFRIEND_H_
#define MISPROGRAMAS_PCSE_TPFINAL_INC_MCUFRIEND_H_

#include "sapi.h"

//todos los valores deben ser pasados como cadenas de caracteres
void tftInit();  //inicializar el display
void tftPrint(uint8_t* text, uint32_t bufferSize); //text: texto a enviar, bufferSize: cantidad de caracteres
void tftFillScreen(uint8_t* color); // Color en 16 bits
void tftSetCursor(uint8_t* x, uint8_t* y); // posiciones en pixeles
void tftDrawRect(uint8_t* x, uint8_t* y, uint8_t* w, uint8_t* h, uint8_t* color); //dibuja rectangulo: x-y izquierda superior, w-h ancho y altura
void tftSetTextColor(uint8_t* c); //Color en 16 bits
void tftSetTextSize(uint8_t* s); //tamaño del texto
void tftDrawLine(uint8_t* x0, uint8_t* y0, uint8_t* x1, uint8_t* y1, uint8_t* color); //dibula linea, punto inicial y final en pixeles
void tftDrawPixel(uint8_t* x, uint8_t* y, uint8_t* color); // dibuja un pixel

#endif /* MISPROGRAMAS_PCSE_TPFINAL_INC_MCUFRIEND_H_ */
