/**
 * @file ioport.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/ioport.h"

inline uint8_t inb(uint16_t portid)	{
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0;"
                 :"=a"(ret)
                 :"Nd"(portid));
    return ret;
}

inline void outb(uint16_t portid, uint8_t val) {
    __asm__ __volatile__("outb %%al, %%dx;"
                 :
                 :"a"(val), "Nd"(portid));
}

inline uint16_t inw(uint16_t portid) {
    uint16_t ret;
    __asm__ __volatile__("inw %1, %0;"
                 :"=a"(ret)
                 :"Nd"(portid));
    return ret;
}

inline void outw(uint16_t portid, uint16_t val) {
    __asm__ __volatile__("outw %%ax, %%dx"
                 :
                 :"a"(val), "Nd"(portid));
}

inline uint32_t inl(uint16_t portid) {
    uint32_t ret;
    __asm__ __volatile__("inl %1, %0;"
                 :"=a"(ret)
                 :"Nd"(portid));
    return ret;
}

inline void outl(uint16_t portid, uint32_t val) {
    __asm__ __volatile__("outl %%eax, %%dx;"
                 :
                 :"a"(val), "Nd"(portid));
}