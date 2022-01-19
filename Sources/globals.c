/*
 * globals.c
 *
 *  Created on: Jul 1, 2017
 *      Author: Ian
 */

#include "PE_types.h"

uint16_t CANRX_timestamp[4] = {0,0,0,0};
uint16_t CANRX_timestamp_prev[4] = {0,0,0,0};
uint8_t CANRX_data[4][8] = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};

uint16_t ms = 0;
uint16_t ms_rollovers = 0;
uint16_t ms_last = 0xFFFF;
uint16_t timer = 0;

uint16_t mV1 = 0;
uint16_t mV2 = 0;
