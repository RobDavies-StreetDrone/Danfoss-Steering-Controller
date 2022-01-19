/*
 * lookup.h
 *
 *  Created on: Jul 13, 2017
 *      Author: Ian
 */

#ifndef LOOKUP_H_
#define LOOKUP_H_

// includes
#include "PE_types.h"

uint16_t lookup_u16_u16(uint16_t X_value, volatile const uint16_t * p_X_axis, volatile const uint16_t * p_Y_axis, uint16_t breakpoints);
int16_t lookup_s16_s16(int16_t X_value, volatile const int16_t * p_X_axis, volatile const int16_t * p_Y_axis, uint16_t breakpoints);
int16_t lookup_u16_s16(uint16_t X_value, volatile const uint16_t * p_X_axis, volatile const int16_t * p_Y_axis, uint16_t breakpoints);

#endif /* LOOKUP_H_ */
