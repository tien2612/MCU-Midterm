/*
 * input_processing.h
 *
 *  Created on: Oct 24, 2022
 *      Author: Tien
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

void button_processing(void);
void fsm_for_input_processing(void);
void fsm_mode_running(void);
void fsm_mode_running_for_pressed_1s(void);
void normal_running_traffic_light(void);
int WhichButtonIsPressed();
int WhichButtonIsPressed3s();
#endif /* INC_INPUT_PROCESSING_H_ */
