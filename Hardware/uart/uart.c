#include "uart.h"

/* 静态变量 */
static UART_HandleTypeDef *g_huart = NULL;  /* UART句柄 */
static LogLevel g_logLevel = LOG_LEVEL_INFO;  /* 默认日志级别 */
static const s8 *g_logLevelName[] = {
    "NONE", "ERROR", "WARN", "INFO", "DEBUG", "VERBOSE"
};

/**
 * @brief 初始化UART
 * @param huart UART句柄指针
 * @return None
 */
void UART_Init(UART_HandleTypeDef *huart)
{
    g_huart = huart;
}

/**
 * @brief 设置日志级别
 * @param level 日志级别
 * @return None
 */
void UART_SetLogLevel(LogLevel level)
{
    // 检查日志级别是否在有效范围内
    if (level < LOG_LEVEL_NONE || level > LOG_LEVEL_VERBOSE)
    {
        g_logLevel = LOG_LEVEL_INFO;  // TODO: 若设置无效级别，将自动替换为默认级别
    }
    else
    {
        g_logLevel = level;
    }
}

/**
 * @brief 获取当前日志级别
 * @return 当前日志级别
 */
LogLevel UART_GetLogLevel(void)
{
    return g_logLevel;
}

/**
 * @brief 通过UART发送字符串
 * @param str 要发送的字符串
 * @return None
 */
void UART_SendString(const s8 *str)
{
    // 只有在串口句柄不为空（串口初始化完成）且含有字符串数据时才发送
    if (g_huart == NULL || str == NULL)
    {
        return;
    }

    HAL_UART_Transmit(g_huart, (u8 *)str, strlen(str), 100);
}

/**
 * @brief 通过UART发送格式化日志
 * @param level 日志级别
 * @param color 日志颜色
 * @param file 源文件名
 * @param line 行号
 * @param format 格式化字符串
 * @param ... 可变参数
 * @return None
 */
void UART_Log(LogLevel level, const s8 *color, const s8 *file, s32 line, const s8 *format, ...)
{
    /* TODO: 检查日志级别 */
    // 这里的使用场景是：当我debug结束后懒得删除加了debug调试信息的代码，这时候把日志级别设为INFO，那么只会输出关键的信息日志，不会输出调试日志了。
    if (level > g_logLevel || g_huart == NULL)
    {
        return;
    }

    /* 临时缓冲区 */
    s8 log_buffer[256];
    s8 *filename = NULL;

    /* 提取短文件名 */
    filename = strrchr(file, '\\');
    if (filename != NULL)
    {
        filename++; /* 跳过反斜杠 */
    }
    else
    {
        filename = (s8 *)file;
    }

    /* 格式化日志头部 */
    s32 head_len = snprintf(log_buffer, sizeof(log_buffer),
                         "%s[%s](%s:%d) ",
                         color, g_logLevelName[level], filename, line);

    /* 格式化可变参数 */
    va_list args;
    va_start(args, format);
    vsnprintf(log_buffer + head_len, sizeof(log_buffer) - head_len - 3, format, args);
    va_end(args);

    /* 添加颜色复位和换行 */
    strcat(log_buffer, LOG_COLOR_RESET);
    strcat(log_buffer, "\r\n");

    /* 发送到串口 */
    HAL_UART_Transmit(g_huart, (u8 *)log_buffer, strlen(log_buffer), 100);
}

/**
 * @brief 重定向printf到UART
 * @param ch 字符
 * @param f 文件指针（未使用）
 * @return 发送的字符
 */
int fputc(int ch, FILE *f)
{
    if (g_huart != NULL)
    {
        u8 temp = (u8)ch;
        HAL_UART_Transmit(g_huart, &temp, 1, 10);
    }
    return ch;
}