/**
 * @file spinlock.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/spinlock.h"
#include "../include/lib64/string.h"
#include "../include/asm.h"
#include "../include/lib64/logging.h"
#include "../include/lapic.h"

void spinlock_init(struct spinlock * lock) {
    memset(lock, 0x0, sizeof(struct spinlock));
    lock->cpu = 0xff;
}

void spinlock_acquire_raw(struct spinlock * lock) {
    while (xchg32(&lock->lock, 1) != 0);
    barrier();
    lock->cpu = cpu();
#if defined (DEBUG)
#endif
}

void spinlock_release_raw(struct spinlock * lock) {
    //ASSERT(lock->cpu == cpu() && lock->lock == 1);
    lock->cpu = 0xff;
    barrier();
    xchg32(&lock->lock, 0);
}