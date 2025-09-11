#include "delay.h"
#include "stm32g4xx_hal.h"

static u32 fac_us = 0;                   // us延时倍乘数（u32类型提高精度）
static u32 fac_ms = 0;                   // ms延时倍乘数（u32类型）

// 初始化延迟函数
void delay_init(u32 SYSCLK)
{
    // TODO: 配置SysTick时钟源为 HCLK(系统时钟频率)
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;   // SysTick时钟频率 = HCLK时钟频率 = 170MHz

    // 计算延时倍乘数
    fac_us = SYSCLK;                               // 例如170MHz -> 每微秒170个周期
    fac_ms = fac_us * 1000;                        // 每毫秒的周期数 = 微秒周期数 × 1000
}

// 微秒级延时
void delay_us(u32 nus)
{
    if (nus == 0)
    {
        return;
    }

    u32 temp;
    // 设置重装载值 (nus * fac_us - 1)，因为SysTick从LOAD值递减到0时共计LOAD+1个周期
    SysTick->LOAD = nus * fac_us - 1;  // 加载延时所需的计数值
    SysTick->VAL = 0x00;               // 清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // 开始计时

    do
    {
        temp = SysTick->CTRL;
    }
    while ((temp & 0x01) && !(temp & (1 << 16))); // 等待时间到达

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
    SysTick->VAL = 0x00;           // 清空计数器
}

// 毫秒级延时分块函数
// (0xFFFFFF * (1 / 170e6)) * 1000 ms = 16777215 / 170000000 * 1000 = 98.6895 ms
void delay_xms(u32 nms)
{
    if (nms == 0)
    {
        return;
    }

    u32 temp;
    // 设置重装载值 (nms * fac_ms - 1)，确保不会超过24位计数器的最大值
    SysTick->LOAD = nms * fac_ms - 1;  // 加载延时所需的计数值
    SysTick->VAL = 0x00;               // 清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // 开始计时

    do
    {
        temp = SysTick->CTRL;
    }
    while ((temp & SysTick_CTRL_ENABLE_Msk) && !(temp & SysTick_CTRL_COUNTFLAG_Msk)); // 等待时间到达 (COUNTFLAG位置位)

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
    SysTick->VAL = 0x00;           // 清空计数器
}

// 毫秒级延时(可以延迟任意毫秒)
void delay_ms(u32 nms)
{
    if (nms == 0)
    {
        return;
    }

    // 计算分块延时参数 (SysTick是24位计数器，最大值0xFFFFFF，约支持98ms@170MHz)
    u32 max_delay = 0xFFFFFF / fac_ms; // 计算24位计数器能支持的最大毫秒数
    if (max_delay > 90)
    {
        max_delay = 90; // 保守设置为90ms，确保不会溢出
    }

    u32 repeat = nms / max_delay;      // 分块次数
    u32 remain = nms % max_delay;      // 剩余时间

    while (repeat--)                   // 延时超过max_delay时分块处理
    {
        delay_xms(max_delay);
    }
    if (remain)                        // 处理剩余时间
    {
        delay_xms(remain);
    }
}
