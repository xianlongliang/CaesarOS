#include "../include/lib64/logging.h"
#include <stdarg.h>
#include "../include/lib64/string.h"

// log verbosity option[LOG_TRIVIA, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR]
#define DEFAULT_LOGGING_LEVEL LOG_DEBUG

int __log_level = DEFAULT_LOGGING_LEVEL;

struct spinlock __logging_lock;

__attribute__((constructor)) void logging_pre_init(void) {
    spinlock_init(&__logging_lock);
}