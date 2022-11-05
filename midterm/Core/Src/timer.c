/*
 * timer.c
 *
 *  Created on: Oct 24, 2022
 *      Author: Tien
 */

#ifndef SRC_TIMER_C_
#define SRC_TIMER_C_

#include "main.h"
#include "input_processing.h"
#include "input_reading.h"
#include "software_timer.h"
#include "led7seg.h"
#include "global.h"

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim ) {
	if (htim->Instance == TIM2) {
		button_reading();
	}
	timerRun();
}

#endif /* SRC_TIMER_C_ */
