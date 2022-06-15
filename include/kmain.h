/**
 * @file kmain.h
 * @author liang.xianlong@zte.com.cn
 * @brief kmain.h 
 * @version 0.1
 * @date 2022-06-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __KMAIN_H__
#define __KMAIN_H__

#include <stdint.h>

 /**
  * This is the entrypoint of the kernel (C code).
  *
  * @param addr the multiboot info address
  */

  void kmain(uintptr_t addr) __asm__("kmain");

#endif