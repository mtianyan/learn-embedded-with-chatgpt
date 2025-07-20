好的，下面我将为你完整讲解 **看门狗定时器（WDOG）** 的工作原理，并结合 i.MX6ULL 给出一个 **裸机使用示例**，包括：工作机制、初始化流程、喂狗操作，以及程序卡死时自动复位的原理和代码实现。

---

## 🧠 一、WDOG 看门狗定时器工作原理

### 📌 概念

看门狗定时器（Watchdog Timer, 简称 WDOG）是一种 **防止系统失控** 的安全机制，通常用于嵌入式系统中自动 **检测程序是否死机**，并在超时时 **复位芯片**。

### 🧩 工作机制

1. **启动看门狗** 后，它开始倒计时。
2. 正常运行时，程序会在周期性“喂狗”（写入特定值）来重装计时器。
3. 如果程序发生异常/死循环，没有及时喂狗 → 超时 → **自动复位系统**。

---

## 📐 二、i.MX6ULL 看门狗定时器（WDOG1）

* i.MX6ULL 有两个硬件看门狗：`WDOG1` 和 `WDOG2`。
* 我们这里使用 `WDOG1`。

### 📍 寄存器基地址

```c
#define WDOG1_BASE   0x020BC000
```

### 📍 常用寄存器

| 寄存器    | 偏移   | 说明              |
| ------ | ---- | --------------- |
| `WCR`  | 0x00 | 控制寄存器           |
| `WSR`  | 0x02 | 喂狗寄存器           |
| `WRSR` | 0x04 | 复位状态            |
| `WICR` | 0x06 | 中断控制            |
| `WMCR` | 0x08 | Misc控制（如：使能软复位） |

---

## ⚙️ 三、裸机看门狗使用步骤

### ✅ 1. 启用看门狗

```c
#define WDOG1_WCR     (*(volatile unsigned short *)(WDOG1_BASE + 0x00))
#define WDOG1_WSR     (*(volatile unsigned short *)(WDOG1_BASE + 0x02))
#define WDOG1_WRSR    (*(volatile unsigned short *)(WDOG1_BASE + 0x04))
#define WDOG1_WICR    (*(volatile unsigned short *)(WDOG1_BASE + 0x06))
#define WDOG1_WMCR    (*(volatile unsigned short *)(WDOG1_BASE + 0x08))

void wdog_init(void) {
    // 使能看门狗，并设置超时时间（默认单位为0.5ms，256*0.5ms=128ms）
    WDOG1_WCR = (1 << 2)  | // WDE = 1 使能看门狗
                (1 << 3)  | // WDBG = 1 调试时看门狗继续计时
                (1 << 0);   // WDE = 1

    // 第一次喂狗（必须写两次）
    WDOG1_WSR = 0x5555;
    WDOG1_WSR = 0xAAAA;
}
```

### ✅ 2. 喂狗函数

```c
void wdog_feed(void) {
    WDOG1_WSR = 0x5555;
    WDOG1_WSR = 0xAAAA;
}
```

---

## 🧪 四、测试程序（main.c）

```c
#include "imx6ull.h"

extern void wdog_init(void);
extern void wdog_feed(void);

int main(void) {
    wdog_init();  // 初始化并开启看门狗

    while (1) {
        // 模拟正常程序执行，喂狗
        wdog_feed();

        // 模拟延时（< 看门狗超时时间）
        for (volatile int i = 0; i < 1000000; i++);
    }

    return 0;
}
```

---

## 🛑 五、测试“程序卡死”

你可以注释掉 `wdog_feed()` 来模拟程序死循环或卡住：

```c
int main(void) {
    wdog_init();

    while (1) {
        // wdog_feed(); // 注释掉喂狗
        for (volatile int i = 0; i < 1000000; i++);
    }

    return 0;
}
```

程序在 128ms 左右没有喂狗，就会触发 **系统复位**。

---

## 🔍 六、进阶说明

* `WRSR` 可用于判断是否为看门狗复位。
* `WDOG1_WMCR` 可以禁止软复位功能，但我们通常保持开启。
* 默认时钟源是 `24MHz`，并除以内部分频得到计时频率。

---

## 🧾 七、总结

| 功能       | 方法             |
| -------- | -------------- |
| 初始化      | `wdog_init()`  |
| 喂狗       | `wdog_feed()`  |
| 模拟死机     | 注释喂狗代码         |
| 超时自动复位系统 | 由 `WDOG1` 硬件完成 |

---

如果你需要：

* 添加串口提示“系统复位中”
* 修改超时时间
* 将喂狗放入定时器中断中
* 添加 WRSR 检查复位原因

都可以继续告诉我，我来帮你完善这个 Demo。
