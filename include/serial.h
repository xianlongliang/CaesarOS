/**
 * @file serial.h

 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "ioport.h"

int is_transmit_empty(void);

void write_serial(uint8_t a);

#endif