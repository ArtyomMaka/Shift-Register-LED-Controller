/*
 * shift_register.c
 *
 *  Created on: Jul 4, 2025
 *      Author: makar
 */

#include "shift_register.h"
#include <stdbool.h>

#define SERIAL_INPUT                	  GPIO_PIN_1
#define OUTPUT_ENABLE               	  GPIO_PIN_2
#define STORAGE_REGISTER_CLOCK      	  GPIO_PIN_3
#define SHIFT_REGISTER_CLOCK        	  GPIO_PIN_4

#define SERIAL_INPUT_SET()           	  HAL_GPIO_WritePin(GPIOA, SERIAL_INPUT, SET);
#define OUTPUT_ENABLE_SET()          	  HAL_GPIO_WritePin(GPIOA, OUTPUT_ENABLE, SET);
#define STORAGE_REGISTER_CLOCK_SET()      HAL_GPIO_WritePin(GPIOA, STORAGE_REGISTER_CLOCK, SET);
#define SHIFT_REGISTER_CLOCK_SET()        HAL_GPIO_WritePin(GPIOA, SHIFT_REGISTER_CLOCK, SET);

#define SERIAL_INPUT_RESET()           	  HAL_GPIO_WritePin(GPIOA, SERIAL_INPUT, RESET);
#define OUTPUT_ENABLE_RESET()          	  HAL_GPIO_WritePin(GPIOA, OUTPUT_ENABLE, RESET);
#define STORAGE_REGISTER_CLOCK_RESET()    HAL_GPIO_WritePin(GPIOA, STORAGE_REGISTER_CLOCK, RESET);
#define SHIFT_REGISTER_CLOCK_RESET()      HAL_GPIO_WritePin(GPIOA, SHIFT_REGISTER_CLOCK, RESET);

void shift_register_init(){
	SERIAL_INPUT_RESET();
	OUTPUT_ENABLE_RESET();
	STORAGE_REGISTER_CLOCK_RESET();
	SHIFT_REGISTER_CLOCK_RESET();
}
void shift_register_off(){
	OUTPUT_ENABLE_SET();
}
void shift_register_on(){
	OUTPUT_ENABLE_RESET();
}

void shift_register_state(long long shift_register_count, long long change_state){

	STORAGE_REGISTER_CLOCK_RESET();

	for(uint8_t i = 0; i < 8 * shift_register_count; ++i){

		bool bitValue = (change_state >> i) & 1;

		if(bitValue){
			SERIAL_INPUT_SET();
		}
		else {
			SERIAL_INPUT_RESET();
		}

		SHIFT_REGISTER_CLOCK_SET();
		SHIFT_REGISTER_CLOCK_RESET();
	}
	STORAGE_REGISTER_CLOCK_SET();
}

//PORTB &= ~(1 << STORAGE_REGISTER_CLOCK);
//  for (uint8_t i = 0; i < 16; ++i) {
//
//    bool bitValue = ((change_state >> i) & 1);
//
//    if (bitValue){
//
//      PORTB |= (1 << SERIAL_INPUT);
//
//    }
//    else {
//
//      PORTB &= ~(1 << SERIAL_INPUT);
//
//    }
//
//    PORTB |= (1 << SHIFT_REGISTER_CLOCK);
//    PORTB &= ~(1 << SHIFT_REGISTER_CLOCK);
//
//  }
//
//  PORTB |= (1 << STORAGE_REGISTER_CLOCK);
