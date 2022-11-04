/*
 * input_processing.c
 *
 *  Created on: Oct 24, 2022
 *      Author: TIEN
 */
#include "input_reading.h"
#include "input_processing.h"
#include "stdio.h"
#include "global.h"
#include "software_timer.h"
#include "led7seg.h"
#include "traffic_light_processing.h"

enum ButtonState{
	BUTTON_RELEASED,
	BUTTON_PRESSED,
	BUTTON_PRESS_MORE_THAN_1S
};

enum ButtonState buttonState = BUTTON_RELEASED;

int WhichButtonIsPressed() {
	if (is_button_pressed(3)) return button_reset_is_pressed;
	if (is_button_pressed(0)) return button_mode_is_pressed;
	if (is_button_pressed(1)) return button_add_is_pressed;
	if (is_button_pressed(2)) return button_confirm_is_pressed;

	return 0; // None of these buttons are pressed
}

int WhichButtonIsPressed1s() {
	if (is_button_pressed_1s(3)) return button_reset_is_pressed_1s;
	if (is_button_pressed_1s(0)) return button_mode_is_pressed_1s;
	if (is_button_pressed_1s(1)) return button_add_is_pressed_1s;
	if (is_button_pressed_1s(2)) return button_confirm_is_pressed_1s;

	return 0; // None of these buttons are pressed
}
void fsm_mode_running() {
	switch(WhichButtonIsPressed()) {
		// NORMAL MODE
		case button_mode_is_pressed:
			switch(status) {
				// NORMAL MODE - Automatic Running
				case NORMAL_MODE:
					led_init();
					status = RED_MODE;
					printf("The system is in MODE '2 - RED_MODE' \r\n");
					light_time = man_red_time;
					temp_value = light_time;
					// Adjust frequency scanning process of single RED LED
					setTimer1(DURATION_HALF_OF_SECOND);
					break;
				// RED && MAN_RED MODE
				case RED_MODE: case MAN_RED_MODE:
					led_init();
					// restore light_time if is not pressed button confirm
					light_time = man_amber_time;
					temp_value = light_time; // store value to temp variable if button add is pressed
					status = AMBER_MODE;
					printf("The system is in MODE '3 - AMBER_MODE' \r\n");
					break;
				// AMBER && MAN_AMBER MODE
				case AMBER_MODE: case MAN_AMBER_MODE:
					GPIOB->BSRR = 0x3F00;
					// restore light_time if is not pressed button confirm
					light_time = man_green_time;
					temp_value = light_time; // store value to temp variable if button add is pressed
					status = GREEN_MODE;
					printf("The system is in MODE '4 - GREEN_MODE' \r\n");
					break;
				// GREEN && MAN_GREEN MODE
				case GREEN_MODE: case MAN_GREEN_MODE:
					led_init();
					// restore light_time if is not pressed button confirm
					light_time = man_red_time;
					// assign temp value = light_time and then
					// if button add is pressed it will increase temp_value;
					temp_value = light_time;
					status = NORMAL_MODE;
					printf("The system is in MODE '1 - NORMAL' \r\n");
					// re-initialize traffic light
					traffic_init();
					// update the new buffer to display it at LED 7 SEG
					update_buffer();
					setTimer3(DURATION_1S);
				default:
					break;
			}
			buttonState = BUTTON_PRESSED;
			break;
		// ADD BUTTON
		case button_add_is_pressed:
			// Increasing time depending on current state
			switch(status) {
			case RED_MODE:
				status = MAN_RED_MODE;
				break;
			case AMBER_MODE:
				status = MAN_AMBER_MODE;
				break;
			case GREEN_MODE:
				status = MAN_GREEN_MODE;
				break;
			default:
				break;
			}
			// If the button add is pressed then temp_value++. Finally update light_time = temp_value,
			updateTempTime();
			break;
		// CONFIRM BUTTON
		case button_confirm_is_pressed:
			// If the button confirm is pressed, then man_red/yellow/green_time = temp_value was stored before
			confirmAdjustedTime();
			break;
		case button_reset_is_pressed:
			resetToTheDefaultSetting();
			break;
		default:
			break;
	}
}

void fsm_mode_running_for_pressed_1s() {
	if (status == RED_MODE || status == GREEN_MODE || status == AMBER_MODE)
		light_time1 = status;
	switch(WhichButtonIsPressed1s()) {
		// NORMAL MODE
		case button_mode_is_pressed_1s:
			switch(status) {
				// NORMAL MODE - Automatic Running
				case NORMAL_MODE:
					led_init();
					status = RED_MODE;
					printf("The system is in MODE '2 - RED_MODE' \r\n");
					light_time = man_red_time;
					temp_value = light_time;
					// Adjust frequency scanning process of single RED LED
					setTimer1(DURATION_HALF_OF_SECOND);
					break;
				// RED && MAN_RED MODE
				case RED_MODE: case MAN_RED_MODE:
					led_init();
					// restore light_time if is not pressed button confirm
					light_time = man_amber_time;
					temp_value = light_time; // store value to temp variable if button add is pressed
					status = AMBER_MODE;
					printf("The system is in MODE '3 - AMBER_MODE' \r\n");
					break;
				// AMBER && MAN_AMBER MODE
				case AMBER_MODE: case MAN_AMBER_MODE:
					GPIOB->BSRR = 0x3F00;
					// restore light_time if is not pressed button confirm
					light_time = man_green_time;
					temp_value = light_time; // store value to temp variable if button add is pressed
					status = GREEN_MODE;
					printf("The system is in MODE '4 - GREEN_MODE' \r\n");
					break;
				// GREEN && MAN_GREEN MODE
				case GREEN_MODE: case MAN_GREEN_MODE:
					led_init();
					// restore light_time if is not pressed button confirm
					light_time = man_red_time;
					// assign temp value = light_time and then
					// if button add is pressed it will increase temp_value;
					temp_value = light_time;
					status = NORMAL_MODE;
					printf("The system is in MODE '1 - NORMAL' \r\n");
					// re-initialize traffic light
					traffic_init();
					// update the new buffer to display it at LED 7 SEG
					update_buffer();
					setTimer3(DURATION_1S);
				default:
					break;
			}
			buttonState = BUTTON_PRESSED;
			break;
		// ADD BUTTON
		case button_add_is_pressed_1s:
			// Increasing time depending on current state
			switch(status) {
			case RED_MODE:
				status = MAN_RED_MODE;
				break;
			case AMBER_MODE:
				status = MAN_AMBER_MODE;
				break;
			case GREEN_MODE:
				status = MAN_GREEN_MODE;
				break;
			default:
				break;
			}
			// If the button add is pressed then temp_value++. Finally update light_time = temp_value,
			updateTempTime();
			break;
		// CONFIRM BUTTON
		case button_confirm_is_pressed:
			// If the button confirm is pressed, then man_red/yellow/green_time = temp_value was stored before
			confirmAdjustedTime();
			break;
		case button_reset_is_pressed:
			resetToTheDefaultSetting();
			break;
		default:
			break;
	}
}

void fsm_for_input_processing() {
	// Only display 3 MODE to modify value.
	if (status == RED_MODE || status == GREEN_MODE || status == AMBER_MODE)
		light_time1 = status;
	switch(buttonState) {
		case BUTTON_RELEASED:
			AllowToExecuteAfterASecondPressed = 0;
			if (WhichButtonIsPressed()) {
				buttonState = BUTTON_PRESSED;
				fsm_mode_running();
				//break;
			}
		case BUTTON_PRESSED:
			if (!WhichButtonIsPressed()) {
				buttonState = BUTTON_RELEASED;
			} else {
				for (int i = 0; i < N0_OF_BUTTONS; i++) {
					if (is_button_pressed_1s(i))
						buttonState = BUTTON_PRESS_MORE_THAN_1S;
				}
			}
			break;
		case BUTTON_PRESS_MORE_THAN_1S:
			//firstLongPressButton = 0;
			if (!WhichButtonIsPressed()) {
				buttonState = BUTTON_RELEASED;
			}
			// TODO
			AllowToExecuteAfterASecondPressed = 1; // Allow the system to count for pressed button each half a second
			for (int i = 0; i < N0_OF_BUTTONS; i++) {
				//firstLongPressButton[i] = 0;
				if (is_button_pressed_one_quarter_second(i)) {
					fsm_mode_running_for_pressed_1s();
					flagForButtonPressOneQuarterSecond[i] = 0;
				}
			}
			break;
		default:
			break;
	}
}
