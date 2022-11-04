/*
 * traffic_light_processing.c
 *
 *  Created on: Oct 26, 2022
 *      Author: nguye
 */

#include "main.h"
#include "stdio.h"
#include "traffic_light_processing.h"
#include "input_processing.h"
#include "global.h"
#include "led7seg.h"
#include "software_timer.h"

void traffic_init() {
	light_time = man_green_time;
	light_time1 = man_red_time;
	led_init();
	HAL_GPIO_WritePin(GPIOB, D1_Pin, 0); // On ROAD 1, turn on the RED light. 
	HAL_GPIO_WritePin(GPIOB, D6_Pin, 0); // On ROAD 2, turn on the GREEN light. 
}

void updateTempTime() {
	switch(status) {
		case NORMAL_MODE:
			break;
		case MAN_RED_MODE:
			//light_time = man_red_time;
			if (temp_value >= 99) temp_value = 0;
			else temp_value++;
			break;
		case MAN_AMBER_MODE:
			//temp_value = temp_value;
			if (temp_value >= 99) temp_value = 0;
			else temp_value++;
			break;
		case MAN_GREEN_MODE:
			//light_time = man_green_time;
			if (temp_value >= 99) temp_value = 0;
			else temp_value++;
			break;
	}
	light_time = temp_value;
}

void confirmAdjustedTime() {
	printf("Confirmed adjust time!\r\n");
	switch(status) {
		case NORMAL_MODE:
			//temp_value = light_time;
			break;
		case MAN_RED_MODE:
			man_red_time = temp_value;
			light_time = man_red_time;
			break;
		case MAN_AMBER_MODE:
			man_amber_time = temp_value;
			light_time = man_amber_time;
			break;
		case MAN_GREEN_MODE:
			man_green_time = temp_value;
			light_time = man_green_time;
			break;
		default:
			break;
	}
}

void resetToTheDefaultSetting() {
	// default settings
	printf("All settings have been reset!\r\n");
	printf("The system is in MODE '1 - NORMAL_MODE' \r\n");
	man_red_time = RED_TIME / 100;
	man_amber_time = YELLOW_TIME / 100;
	man_green_time = GREEN_TIME / 100;
	status = NORMAL_MODE;
	led_status = RED_GREEN;
	index_led = 0;
	temp_value = 0;
	// re-initialize traffic light with default settings
	traffic_init();
}

void normal_running_traffic_light() {
	switch(led_status) {
		case RED_GREEN:
			if (timer3_flag == 1) {
				led_init();
				HAL_GPIO_WritePin(GPIOB, D1_Pin, 0); // On ROAD 1, turn on the RED light. 
				HAL_GPIO_WritePin(GPIOB, D6_Pin, 0); // On ROAD 2, turn on the GREEN light. 

				light_time--;
				light_time1--;
				if (light_time == 0 || light_time1 == 0) {
					led_status = RED_AMBER;
					light_time = man_amber_time; // Road 2
					led_init();
					//light_time1 = man_red_time; // Road 1
					HAL_GPIO_WritePin(GPIOB, D1_Pin, 0); // On ROAD 1, turn on the RED light. 
					HAL_GPIO_WritePin(GPIOB, D5_Pin, 0); // On ROAD 2, turn on the AMBER light. 
				}
				setTimer3(DURATION_1S);
			}
			break;
		case RED_AMBER:
				if (timer3_flag == 1) {
					light_time--;
					light_time1--;
					if (!light_time || !light_time1) {
						led_status = GREEN_RED;
						light_time = man_red_time; // Road 2
						light_time1 = man_green_time; // Road 1

						led_init();
						HAL_GPIO_WritePin(GPIOB, D4_Pin, 0); // On ROAD 1, turn on the RED light. 
						HAL_GPIO_WritePin(GPIOB, D3_Pin, 0); // On ROAD 2, turn on the GREEN light. 
					}
					setTimer3(DURATION_1S);
				}

			break;
		case GREEN_RED:
			if (timer3_flag == 1) {

				light_time--;
				light_time1--;
				if (!light_time || !light_time1) {
					led_status = AMBER_RED;
					light_time1 = man_amber_time; // Road 1
					led_init();
					HAL_GPIO_WritePin(GPIOB, D2_Pin, 0); // On ROAD 1, turn on the RED light. 
					HAL_GPIO_WritePin(GPIOB, D4_Pin, 0); // On ROAD 2, turn on the GREEN light. 
				}
				setTimer3(DURATION_1S);
			}

			break;
		case AMBER_RED:
			if (timer3_flag == 1) {
				light_time--;
					light_time1--;
				if (!light_time || !light_time1) {
					led_status = RED_GREEN;
					light_time = man_green_time; // Road 2
					light_time1 = man_red_time; // Road 1
					led_init();
					HAL_GPIO_WritePin(GPIOB, D1_Pin, 0); // On ROAD 1, turn on the RED light. 
					HAL_GPIO_WritePin(GPIOB, D6_Pin, 0); // On ROAD 2, turn on the GREEN light. 
				}
				setTimer3(DURATION_1S);
			}
			break;
		default:
			break;
	}
}

void traffic_light_processing() {
	switch(status) {
		case NORMAL_MODE:
			normal_running_traffic_light();
			break;
		case RED_MODE: case MAN_RED_MODE:
			if (timer1_flag == 1) {
				// Toggle RED
				HAL_GPIO_TogglePin(GPIOB, D4_Pin | D1_Pin);
				setTimer1(DURATION_HALF_OF_SECOND);
			}
			break;
		case AMBER_MODE: case MAN_AMBER_MODE:
			if (timer1_flag == 1) {
				// Toggle AMBER
				HAL_GPIO_TogglePin(GPIOB, D2_Pin | D5_Pin);
				setTimer1(DURATION_HALF_OF_SECOND);
			}
			break;
		case GREEN_MODE: case MAN_GREEN_MODE:
			if (timer1_flag == 1) {
				// Toggle GREEN
				HAL_GPIO_TogglePin(GPIOB, D3_Pin | D6_Pin);
				setTimer1(DURATION_HALF_OF_SECOND);
			}
			break;
	}
}
