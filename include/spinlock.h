/**
 * @file spinlock.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __SPINLOCK_H__
#define __SPINLOCK_H__

#include "atomic.h"

struct spinlock {
    uint32_t lock;
    uint32_t cpu;
    void * blob;
#if defined(DEBUG)
#define MAX_CALLING_FRAME 32
    uint64_t backtrace[32];
#endif
};

void spinlock_init(struct spinlock * lock);

void spinlock_acquire_raw(struct spinlock * lock);

void spinlock_release_raw(struct spinlock * lock);

#endif