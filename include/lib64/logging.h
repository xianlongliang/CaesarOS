/**
 * @file logging.h
 * @author liang.xianlong@zte.com.cn
 * @brief kernel logging declaration
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __LOGGING_H__
#define __LOGGING_H__

#include "printk.h"
#include "../spinlock.h"

extern int __log_level;

enum log_level {
    LOG_TRIVIA = 0,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_ASSERT
};

#define pr_debug(format, ...) {\
    if (__log_level <= LOG_DEBUG) { \
        printk("[debug] %s:%d "format, __FILE__, __LINE__, ##__VA_ARGS__); \
    } \
}

#define pr_info(format, ...) { \
    if (__log_level <= LOG_INFO) { \
        printk("[info] %s:%d "format, __FILE__, __LINE__, ##__VA_ARGS__); \
    } \
}

#define pr_error(format, ...) {\
    if (__log_level <= LOG_ERROR) { \
        printk("[error] %s:%d "format, __FILE__, __LINE__, ##__VA_ARGS__); \
    } \
}

#define pr_warn(format, ...) {\
    if (__log_level <= LOG_WARN) { \
        printk("[warn] %s:%d "format, __FILE__, __LINE__, ##__VA_ARGS__); \
    } \
}

/*void __do_assertion(const char * msg, ...);

#define ASSERT(cond) {\
    if (__log_level <= LOG_ASSERT) { \
        if (!(cond)){ \
            __do_assertion("[assert] %s:%d assertion:%s failed\n", \
                           __FILE__, __LINE__, #cond); \
            __asm__ volatile("1:cli;" \
                "hlt;" \
                "jmp 1b;"); \
        }\
    } \
}*/

#define __NOT_REACHED 0x0
#define __not_reach() ASSERT(__NOT_REACHED)

#endif