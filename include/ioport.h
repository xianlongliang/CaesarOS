/**
 * @file ioport.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __IOPORT_H__
#define __IOPORT_H__

#include "./lib64/type.h"

uint8_t inb(uint16_t portid);

void outb(uint16_t portid, uint8_t val);

uint16_t inw(uint16_t portid);

void outw(uint16_t portid, uint16_t val);

uint32_t inl(uint16_t portid);

void outl(uint16_t portid, uint32_t val);

#endif