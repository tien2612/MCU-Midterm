/*
 * global.h
 *
 *  Created on: Oct 24, 2022
 *      Author: Tien
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

// declare the duration of all default leds 

#define button_inc_is_pressed				10
#define button_dec_is_pressed				11
#define button_reset_is_pressed				12

#define button_inc_is_pressed_3s			14
#define button_dec_is_pressed_3s			15
#define button_reset_is_pressed_3s			16

#define DURATION_FOR_AUTO_DECREASING		10000
#define DURATION_1S							1000
#define DURATION_HALF_OF_SECOND				500

extern int counter;
extern int flagForFirstButtonIsReleased;
extern int flagForButtonPress1sWhileHolding[3];
extern int AllowToExecuteAfterASecondPressed;
#endif /* INC_GLOBAL_H_ */
