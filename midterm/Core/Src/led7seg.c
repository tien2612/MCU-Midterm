/*
 * led7seg.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Tien
 */

#include "main.h"
#include "led7seg.h"
#include "global.h"
static uint8_t led7seg[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void display7SEG(int num) {
	GPIOB->BRR= 0xFF;
	GPIOB->BSRR = led7seg[num];
}
