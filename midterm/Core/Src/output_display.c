/*
 * output_display.c
 *
 *  Created on: Oct 25, 2022
 *      Author: TIEN
 */
#include "main.h"
#include "output_display.h"

extern UART_HandleTypeDef huart1;

int _write(int file, char *ptr, int len)
{
	/* Implement your write code here, this is used by puts and printf for example */
	HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, HAL_MAX_DELAY);
	return len;
}


