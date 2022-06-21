/**
 * @file panic.h
 * @author liang.xianlong@zte.com.cn
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __PANIC_H__
#define __PANIC_H__
#include "type.h"

void backtrace(void);

struct auxiliary_state64 {
	uint64_t cpu;
    uint64_t idt_base; // IDT register
    uint64_t idt_size;
    uint64_t TR;   // task regiser
    uint64_t gdt_base; // GDT regiser
    uint64_t gdt_size;
    uint64_t GS_BASE_MSR;
    uint64_t FS_BASE_MSR;
    uint64_t EFER_MSR;
    uint64_t cr4;
    uint64_t cr3;
    uint64_t cr2;
    uint64_t cr0;
};

#define MAX_FRAMES_TO_DUMP 32

struct backtrace_blob {
    uint64_t frames[MAX_FRAMES_TO_DUMP];
    int nr_frames;
};

struct backtrace_blob* get_backtrace_blob(void);

void read_auxiliary_state(struct auxiliary_state64 * stat);

void dump_auxiliary_state(struct auxiliary_state64 * stat);

#endif