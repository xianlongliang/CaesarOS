/**
 * @file printk.h
 * @author liang.xianlong@zte.com.cn
 * @brief kernel printk function declaration
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __PRINTK_H__
#define __PRINTK_H__

#include <stdarg.h>
#include "type.h"

void printk(const char* fmt, ...);

void printk_mp_unsafe(const char* fmt, ...);

void printk_mp_raw(const char * fmt, va_list arg_ptr);

#endif