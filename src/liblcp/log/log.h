#pragma once

#include <stdbool.h>

#ifdef DEBUG
    #define LOG_ERROR(msg, fatal) log_error(msg, __func__, __FILE__, __LINE__, fatal)
#else
    #define LOG_ERROR(msg, interrupt);
#endif

void log_error(char* msg, const char* func, const char* file, const int line, bool fatal);
