/**
 * @file kernel.h
 * @author liang.xianlong@zte.com.cn
 * @brief Kernel generic data structure and functions.
 * @version 0.1
 * @date 2022-06-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __KERNEL_H__
#define __KERNEL_H__

// Kilobytes.
#define K 1024
// Megabytes.
#define M (1024 * K)
// Gigabytes.
#define G (1024 * M)

typedef struct pt_regs {
	unsigned long r15;
	unsigned long r14;
	unsigned long r13;
	unsigned long r12;
	unsigned long r11;
	unsigned long r10;
	unsigned long r9;
	unsigned long r8;
	unsigned long rbx;
	unsigned long rcx;
	unsigned long rdx;
	unsigned long rsi;
	unsigned long rdi;
	unsigned long rbp;
	unsigned long ds;
	unsigned long es;
	unsigned long rax;
	unsigned long func;
	unsigned long errcode;
	unsigned long rip;
	unsigned long cs;
	unsigned long rflags;
	unsigned long rsp;
	unsigned long ss;
} pt_regs;

#endif