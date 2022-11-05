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

enum ButtonState{
	BUTTON_RELEASED,
	BUTTON_PRESSED,
	BUTTON_PRESS_MORE_THAN_1S
};

enum ButtonState buttonState = BUTTON_RELEASED;

int WhichButtonIsPressed() {
	if (is_button_pressed(2)) return button_reset_is_pressed;
	if (is_button_pressed(0)) return button_inc_is_pressed;
	if (is_button_pressed(1)) return button_dec_is_pressed;

	return 0; // None of these buttons are pressed
}

int WhichButtonIsPressed1s() {
	if (is_button_pressed_3s(0)) return button_inc_is_pressed_3s;
	if (is_button_pressed_3s(1)) return button_dec_is_pressed_3s;

	return 0; // None of these buttons are pressed
}

void fsm_mode_running() {
	switch(WhichButtonIsPressed()) {
		// INC BUTTON
		case button_inc_is_pressed:
			// Increasing counter
			if (counter >= 9) counter = 0;
			else counter++;
			display7SEG(counter);

			break;
		// DEC BUTTON
		case button_dec_is_pressed:
			// Decreasing counter
			if (counter <= 0) counter = 9;
			else counter--;
			display7SEG(counter);
			break;
		// RESET BUTTON
		case button_reset_is_pressed:
			counter = 0;
			display7SEG(counter);
			break;
		default:
			break;
	}
}

void fsm_mode_running_for_pressed_3s() {
	switch(WhichButtonIsPressed1s()) {
		// INC BUTTON
		case button_inc_is_pressed_3s:
			// Increasing counter
			if (counter >= 9) counter = 0;
			else counter++;
			display7SEG(counter);

			break;
		// DEC BUTTON
		case button_dec_is_pressed_3s:
			// Decreasing counter
			if (counter <= 0) counter = 9;
			else counter--;
			display7SEG(counter);
			break;
		default:
			break;
	}
}

void fsm_for_input_processing() {
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
				for (int i = 0; i < N0_OF_BUTTONS - 1; i++) {
					if (is_button_pressed_3s(i))
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
				if (is_button_pressed_1s_while_holding(i)) {
					fsm_mode_running_for_pressed_3s();
					flagForButtonPress1sWhileHolding[i] = 0;
				}
			}
			break;
		default:
			break;
	}
}
