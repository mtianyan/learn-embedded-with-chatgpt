以下是**第8周·课程安排之第5项：数码管显示 RTC 实时时间**的内容详解：

---

## 🕓 课程目标：

掌握如何读取 RTC 实时时钟模块的时间，并通过数码管（7 段显示器）显示当前的时间数据。

---

## 一、硬件准备

* STM32F103（或其他 STM32 系列）开发板
* RTC 模块（可用板载 RTC 或外接 DS1302 / DS3231）
* 数码管模块（共阳 / 共阴 任选）
* 74HC595（可选，用于节省 GPIO）
* 面包板与跳线

---

## 二、RTC 实时时钟简介

RTC（Real Time Clock）是实时时钟模块，可在断电情况下依旧记录当前时间（需配合电池）。一般具有如下功能：

* 记录年月日、时分秒
* 支持闰年判断
* 低功耗，带独立电源（钮扣电池）

STM32 有内置 RTC，也可以通过 I2C/SPI 接口外接 RTC 芯片。

---

## 三、数码管基础

**数码管种类：**

* 共阳极（A段接正极，GND控制点亮）
* 共阴极（K接地，VCC控制点亮）

**位选+段选显示：**
通常使用动态扫描方式实现多个位的轮流显示。

**使用 74HC595 扩展 GPIO（可选）**
节省 MCU 的 GPIO，通过串行方式控制 8bit 输出。

---

## 四、项目设计思路

1. 初始化 RTC，设置初始时间
2. 每秒读取当前时间
3. 将时间转换为显示格式（如“14:32”）
4. 将数字分拆为个位、十位等，发送给数码管
5. 动态扫描刷新数码管

---

## 五、关键代码逻辑

### 1. 初始化 RTC（以 STM32 内部 RTC 为例）

```c
void RTC_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_DBP;

    RCC->BDCR |= RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL_LSE;

    RTC->CRL |= RTC_CRL_CNF;
    RTC->PRLH = 0;
    RTC->PRLL = 32767;  // 1秒中断
    RTC->CNTH = 0;
    RTC->CNTL = 0;
    RTC->CRL &= ~RTC_CRL_CNF;
}
```

### 2. 获取当前时间

```c
uint32_t get_time(void) {
    return RTC->CNTH << 16 | RTC->CNTL;
}
```

---

## 六、数码管动态显示逻辑

```c
uint8_t digit_to_seg[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void display_time(uint8_t hour, uint8_t min) {
    uint8_t digits[4];
    digits[0] = hour / 10;
    digits[1] = hour % 10;
    digits[2] = min / 10;
    digits[3] = min % 10;

    for (int i = 0; i < 4; i++) {
        set_segment(digit_to_seg[digits[i]]);
        select_digit(i);
        delay_ms(2);  // 保持一点时间
        clear_all();
    }
}
```

---

## 七、项目拓展

* 添加年月日显示功能
* 按键设置时间
* 支持 DS1302 / DS3231 外部 RTC 模块（使用 SPI/I2C）

---

## 八、小结

| 模块   | 技术要点               |
| ---- | ------------------ |
| RTC  | 时间保持、电池供电、寄存器设置    |
| 数码管  | 段码表、动态扫描、位选段选      |
| 项目整合 | 将时间转换成显示格式并分时刷新数码管 |

如果你使用的是 CubeMX + HAL，我也可以提供对应的初始化和显示逻辑代码。是否需要提供 HAL 版本或 DS1302 驱动代码？
