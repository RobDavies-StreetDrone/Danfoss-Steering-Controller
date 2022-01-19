/*
 * globals.h
 *
 *  Created on: Jul 1, 2017
 *      Author: Ian
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "PE_types.h"

extern uint16_t CANRX_timestamp[4];
extern uint16_t CANRX_timestamp_prev[4];
extern uint8_t CANRX_data[4][8];

extern uint16_t ms;
extern uint16_t ms_rollovers;
extern uint16_t ms_last;
extern uint16_t timer;

extern uint16_t mV1;
extern uint16_t mV2;

#endif /* GLOBALS_H_ */
