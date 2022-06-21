/**
 * @file string.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <stdarg.h>
#include "type.h"

void memset(void * dst, uint8_t val, uint64_t size);

void memcpy(void * dst, const void * src, int length);

void sprintf_raw(char * buff, const char * fmt, va_list arg_ptr);


void sprintf(char * buff, const char * fmt, ...);

#endif
