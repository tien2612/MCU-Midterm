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
static uint8_t led_buffer[4] = {0};
//static uint8_t man_led_buffer[3] = {0};
void update_buffer() {
	if (light_time1 >= 10) {
		led_buffer[0] = light_time1 / 10;
		led_buffer[1] = light_time1 % 10;
	} else {
		led_buffer[0] = 0;
		led_buffer[1] = light_time1;
	}

	if (light_time >= 10) {
		led_buffer[2] = light_time / 10;
		led_buffer[3] = light_time % 10;
	} else {
		led_buffer[2] = 0;
		led_buffer[3] = light_time;
	}
}

void led_init() {
	GPIOB->BSRR = 0x3F00;
}

void led_clear() {
	HAL_GPIO_WritePin(GPIOA, D1_Pin | D2_Pin | D3_Pin | D4_Pin | D5_Pin | D6_Pin, 1);
}

void update7SEG(int index){
	switch(index) {
		case 0:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, ON_7SEG); // turn on the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, OFF_7SEG); // turn off the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, OFF_7SEG); // turn off the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, OFF_7SEG); // turn off the fourth SEG
			display7SEG(led_buffer[0]);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, OFF_7SEG); // turn off the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, ON_7SEG); // turn on the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, OFF_7SEG); // turn off the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, OFF_7SEG); // turn off the fourth SEG
			display7SEG(led_buffer[1]);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, OFF_7SEG); // turn off the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, OFF_7SEG); // turn off the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, ON_7SEG); // turn on the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, OFF_7SEG); // turn off the fourth SEG
			display7SEG(led_buffer[2]);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, OFF_7SEG); // turn off the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, OFF_7SEG); // turn off the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, OFF_7SEG); // turn off the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, ON_7SEG); // turn on the fourth SEG
			display7SEG(led_buffer[3]);
			break;
		default:
			break;
	}
}
void display7SEG(int num) {
	GPIOB->BRR= 0xFF;
	GPIOB->BSRR = led7seg[num];
}

void displayMode() {
	update_buffer();
	if (index_led >= 4) index_led = 0;
	update7SEG(index_led++);
}
