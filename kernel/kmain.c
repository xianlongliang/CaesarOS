/**
 * @file kmain.c
 * @author liang.xianlong@zte.com.cn
 * @brief  kernel main function
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/kmain.h"
#include "../include/multiboot2.h"


void kmain(uintptr_t addr) {
    multiboot_info_t* mbi = (multiboot_info_t*)addr;
}