/**
 * @file type.h
 * @author liang.xianlong@zte.com.cn
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TYPE_H__
#define __TYPE_H__

#include <stdint.h>
#include <stdarg.h>

enum ERROR_CODE {
	ERROR_OK = 0,
	ERROR_INVALID,
	ERROR_NOT_NECESSARY,
	ERROR_DUPLICATION,
	ERROR_OUT_OF_MEMORY,
	ERROR_OUT_OF_RESOURCE,
};

#define LIKELY(exp) __builtin_expect(!!(exp), 1)
#define UNLIKELY(exp) __builtin_expect(!!(exp), 0)

#endif
