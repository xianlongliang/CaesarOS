/**
 * @file atomic.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ATOMIC_H__
#define __ATOMIC_H__

#include "./lib64/type.h"

static inline uint32_t xchg32(void * dword_addr, uint32_t exchange_value) {
    uint32_t old_value = 0;
    __asm__ volatile ("lock;"
                      "xchgl %%eax, %[TARGET_MEM]"
                      :"=a"(old_value)
                      :"a"(exchange_value), [TARGET_MEM]"m"(*(uint32_t *)dword_addr)
                      :"cc");
    return old_value;
}

#endif