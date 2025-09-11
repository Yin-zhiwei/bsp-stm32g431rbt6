#ifndef __SYS_H
#define __SYS_H

#include "stm32g4xx.h"

// 操作系统支持配置
// 0: 不支持操作系统
// 1: 支持操作系统(如UCOS)
#define SYSTEM_SUPPORT_OS      0

// 定义常见的数据类型，简化替换
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;
typedef const int16_t sc16;
typedef const int8_t sc8;

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;
typedef __I int16_t vsc16;
typedef __I int8_t vsc8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;
typedef const uint16_t uc16;
typedef const uint8_t uc8;

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;
typedef __I uint16_t vuc16;
typedef __I uint8_t vuc8;

//-----------------------------------------------------------------------------
// 位带操作实现 (适用于Cortex-M4)
// 参考: Cortex-M4 Technical Reference Manual
//-----------------------------------------------------------------------------

// 位带别名区计算宏
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x02000000 + ((addr & 0x000FFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr)        *((volatile uint32_t *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

//-----------------------------------------------------------------------------
// GPIO寄存器地址映射 (STM32G431RBT6特定)
// 参考: RM0440 Reference Manual
//-----------------------------------------------------------------------------

// 输出数据寄存器(ODR)地址
#define GPIOA_ODR_Addr    (GPIOA_BASE + 0x14)  // 0x48000014
#define GPIOB_ODR_Addr    (GPIOB_BASE + 0x14)  // 0x48000414
#define GPIOC_ODR_Addr    (GPIOC_BASE + 0x14)  // 0x48000814
#define GPIOD_ODR_Addr    (GPIOD_BASE + 0x14)  // 0x48000C14
#define GPIOE_ODR_Addr    (GPIOE_BASE + 0x14)  // 0x48001014
#define GPIOF_ODR_Addr    (GPIOF_BASE + 0x14)  // 0x48001414
#define GPIOG_ODR_Addr    (GPIOG_BASE + 0x14)  // 0x48001814

// 输入数据寄存器(IDR)地址
#define GPIOA_IDR_Addr    (GPIOA_BASE + 0x10)  // 0x48000010
#define GPIOB_IDR_Addr    (GPIOB_BASE + 0x10)  // 0x48000410
#define GPIOC_IDR_Addr    (GPIOC_BASE + 0x10)  // 0x48000810
#define GPIOD_IDR_Addr    (GPIOD_BASE + 0x10)  // 0x48000C10
#define GPIOE_IDR_Addr    (GPIOE_BASE + 0x10)  // 0x48001010
#define GPIOF_IDR_Addr    (GPIOF_BASE + 0x10)  // 0x48001410
#define GPIOG_IDR_Addr    (GPIOG_BASE + 0x10)  // 0x48001810

//-----------------------------------------------------------------------------
// GPIO位操作宏 (确保n < 16)
//-----------------------------------------------------------------------------

// GPIOA
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr, n)  // 输出控制
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr, n)  // 输入读取

// GPIOB
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr, n)  // 输出控制
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr, n)  // 输入读取

// GPIOC
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr, n)  // 输出控制
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr, n)  // 输入读取

// GPIOD
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr, n)  // 输出控制
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr, n)  // 输入读取

// GPIOE
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr, n)  // 输出控制
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr, n)  // 输入读取

// GPIOF
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr, n)  // 输出控制
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr, n)  // 输入读取

// GPIOG
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr, n)  // 输出控制
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr, n)  // 输入读取

#endif
