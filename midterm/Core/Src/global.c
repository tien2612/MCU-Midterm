/*
 * global.c
 *
 *  Created on: Oct 24, 2022
 *      Author: Tien
 */


#include "global.h"
#include "main.h"

int counter = 0;

int AllowToExecuteAfterASecondPressed = 0;
int flagForFirstButtonIsReleased = 0;
int flagForButtonPress1sWhileHolding[3] = {0};
