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
#include "../include/lib64/logging.h"
#include "../include/osinfo.h"
#include <stdint.h>

void pr_kernel_info() {
	pr_info("\n\033[1;34m%s\033[0m\n", CAESAROS_ASCII);
	pr_info("%s %s for %s has started\n", KERNEL_NAME, KERNEL_VERSION, KERNEL_TARGET);
}

void kmain(uintptr_t addr, uint32_t magic) {
    multiboot_info_t* mbi = (multiboot_info_t*)addr;
    multiboot_init(mbi);
    pr_kernel_info();
    pr_info("mbi_info:\t0x%x\n", mbi);
    pr_info("magic:\t0x%x\n", magic);
    //fpr_debug("lslslslsl\n");
}