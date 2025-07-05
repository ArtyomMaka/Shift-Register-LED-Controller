/*
 * shift_register.h
 *
 *  Created on: Jul 4, 2025
 *      Author: makar
 */

#ifndef INC_SHIFT_REGISTER_H_
#define INC_SHIFT_REGISTER_H_

#include "stm32f1xx_hal.h"

void shift_register_init(void);
void shift_register_state(long long shift_register_count, long long change_state);

#endif /* INC_SHIFT_REGISTER_H_ */
