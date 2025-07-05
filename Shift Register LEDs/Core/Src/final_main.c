/*
 * final_main.c
 *
 *  Created on: Jul 4, 2025
 *      Author: makar
 */
#define SHIFT_REGISTER_COUNT     2

#include <stdbool.h>
#include "final_main.h"
#include "button.h"
#include "shift_register.h"

int state = 0b0101010101010101;
bool run = true;

void final_main(){
	shift_register_init();
	while(1){
		HAL_Delay(150);
		if(button_up(GPIOA, GPIO_PIN_0)){
			if(run){
				shift_register_off();
			} else {
				shift_register_on();
			}
			run = !run;
		}
		if(run){
			if (state == 0b0101010101010101){
				state = 0b1010101010101010;
			} else {
				state = 0b0101010101010101;
			}
			shift_register_state(SHIFT_REGISTER_COUNT, state);
		}
	}
}
