/**
 * @file lapic.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/cpuid.h"
#include "../include/lapic.h"
#include "../include/lib64/logging.h"
 
inline uint32_t cpu(void) {
    uint32_t eax = 0x1, ebx, ecx, edx;
    CPUID(eax, ebx, ecx, edx);
    return ebx >> 24;
    // XXX: deprecate the code below as the APIC base space may not be mapped
    //uint32_t id_reg = lapic_read(APIC_ID_REGISTER);
    //return id_reg >> 24;
}