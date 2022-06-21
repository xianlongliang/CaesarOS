/**
 * @file asm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ASM_H__
#define __ASM_H__

#include "../include/lib64/type.h"

static inline void	cli(void) {
    __asm__ __volatile__("cli;");
}


static inline void sti(void) {
    __asm__ __volatile__("sti;");
}

static inline void halt(void) {
    __asm__ __volatile__("hlt;");
}


static inline void barrier(void) {
    __asm__ __volatile__(""
                     :
                     :
                     :"memory");
}


static inline uint64_t rdtsc(void) {
    uint32_t eax = 0;
    uint32_t edx = 0;
    __asm__ __volatile__("rdtscp;"
                     :"=a"(eax), "=d"(edx)
                     :
                     :"cc");
    return (((uint64_t)edx) << 32)| (uint64_t)eax;
}

#endif