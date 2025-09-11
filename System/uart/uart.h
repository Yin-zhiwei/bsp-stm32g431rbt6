#ifndef __UART_H
#define __UART_H

#include "sys.h"
#include "stm32g4xx_hal.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/* 日志级别定义 */
typedef enum
{
    LOG_LEVEL_NONE = 0,    /* 不输出任何日志 */
    LOG_LEVEL_ERROR,       /* 只输出错误日志 */
    LOG_LEVEL_WARN,        /* 输出警告和错误日志 */
    LOG_LEVEL_INFO,        /* 输出信息、警告和错误日志 */
    LOG_LEVEL_DEBUG,       /* 输出调试、信息、警告和错误日志 */
    LOG_LEVEL_VERBOSE      /* 输出所有级别日志 */
} LogLevel;

/* 日志颜色定义（兼容ANSI终端） */
#define LOG_COLOR_BLACK    "\033[30m"
#define LOG_COLOR_RED      "\033[31m"
#define LOG_COLOR_GREEN    "\033[32m"
#define LOG_COLOR_YELLOW   "\033[33m"
#define LOG_COLOR_BLUE     "\033[34m"
#define LOG_COLOR_MAGENTA  "\033[35m"
#define LOG_COLOR_CYAN     "\033[36m"
#define LOG_COLOR_WHITE    "\033[37m"
#define LOG_COLOR_RESET    "\033[0m"

/* 颜色格式化 (已经在上面定义了完整的颜色代码，此宏不再需要) */
#define LOG_COLOR(COLOR)   COLOR

/* 日志宏定义 */
#define LOG_E(fmt, ...)    UART_Log(LOG_LEVEL_ERROR, LOG_COLOR_RED, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_W(fmt, ...)    UART_Log(LOG_LEVEL_WARN, LOG_COLOR_YELLOW, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_I(fmt, ...)    UART_Log(LOG_LEVEL_INFO, LOG_COLOR_GREEN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_D(fmt, ...)    UART_Log(LOG_LEVEL_DEBUG, LOG_COLOR_CYAN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_V(fmt, ...)    UART_Log(LOG_LEVEL_VERBOSE, LOG_COLOR_WHITE, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/* 函数声明 */
void UART_Init(UART_HandleTypeDef *huart);
void UART_SetLogLevel(LogLevel level);
LogLevel UART_GetLogLevel(void);
void UART_SendString(const s8 *str);
void UART_Log(LogLevel level, const s8 *color, const s8 *file, s32 line, const s8 *format, ...);
int fputc(int ch, FILE *f);

#endif /* __UART_H */
