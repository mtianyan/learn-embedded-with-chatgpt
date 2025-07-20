好的，下面是关于 **SPI 总线通信原理 + 裸机实现 SPI 外设通信** 的完整讲解。

---

## 📌 一、SPI 总线通信协议简介

SPI（Serial Peripheral Interface）是一种**全双工、同步、主从式**的串行通信协议，广泛用于 MCU 与各种外设（如 Flash、ADC、LCD、RF 模块）之间通信。

---

## 🧱 二、SPI 硬件结构

SPI 通常有以下 4 条线：

| 信号线   | 全称                         | 方向（主设备角度） | 说明            |
| ----- | -------------------------- | --------- | ------------- |
| SCLK  | Serial Clock               | 输出        | 时钟信号          |
| MOSI  | Master Out Slave In        | 输出        | 主机 → 从机 数据    |
| MISO  | Master In Slave Out        | 输入        | 从机 → 主机 数据    |
| CS/SS | Chip Select / Slave Select | 输出        | 从机使能信号（低电平有效） |

---

## 🔁 三、SPI 通信时序图解

以主机发送 `0x9A` 给从机，并读取从机返回 `0xF3` 为例：

```
CS  ────────┐                  ┌──────────────
            └──────────────────┘

SCLK:    ↑ ↓ ↑ ↓ ↑ ↓ ↑ ↓ ↑ ↓ ↑ ↓ ↑ ↓ ↑ ↓   （时钟同步）

MOSI:    1 0 0 1 1 0 1 0         → 0x9A

MISO:                      1 1 1 1 0 0 1 1  → 0xF3
```

> * 数据传输通常在 SCLK 上升/下降沿进行（取决于 SPI 模式）
> * 每次传输 **1 个字节 = 8 个时钟周期**
> * 通常 SPI 使用 **主发送从响应** 模式（读写同步）

---

## 🔧 四、SPI 模式（四种）

SPI 有 4 种模式，由 **CPOL（时钟极性）** 和 **CPHA（时钟相位）** 决定：

| 模式 | CPOL | CPHA | 说明                 |
| -- | ---- | ---- | ------------------ |
| 0  | 0    | 0    | 空闲时 SCLK 为低，采样在上升沿 |
| 1  | 0    | 1    | 空闲时 SCLK 为低，采样在下降沿 |
| 2  | 1    | 0    | 空闲时 SCLK 为高，采样在下降沿 |
| 3  | 1    | 1    | 空闲时 SCLK 为高，采样在上升沿 |

主机与从机必须使用相同模式。

---

## 🧪 五、裸机 SPI 示例：与 SPI Flash 通信（读取 JEDEC ID）

> 以 SPI Flash（如 W25Qxx 系列）为例，实现读取厂商 ID

### ✅ 1. SPI Flash 指令

| 指令     | 说明          | 返回数据             |
| ------ | ----------- | ---------------- |
| `0x9F` | 读取 JEDEC ID | \[厂商ID]\[存储容量ID] |

---

### ✅ 2. 裸机代码核心逻辑

#### 🔧 SPI 引脚初始化（GPIO 模拟 SPI）

```c
void spi_init(void) {
    gpio_init(SCLK_PIN, OUTPUT);
    gpio_init(MOSI_PIN, OUTPUT);
    gpio_init(MISO_PIN, INPUT);
    gpio_init(CS_PIN, OUTPUT);
    gpio_set(CS_PIN, 1);  // 默认不选中
}
```

#### 📤 SPI 写一个字节 & 📥 读一个字节

```c
uint8_t spi_transfer(uint8_t data) {
    uint8_t recv = 0;
    for (int i = 0; i < 8; i++) {
        gpio_set(MOSI_PIN, (data & 0x80) ? 1 : 0);
        data <<= 1;

        gpio_set(SCLK_PIN, 1);
        delay_us(1);  // SPI时钟上升沿
        recv <<= 1;
        if (gpio_get(MISO_PIN)) recv |= 0x01;
        gpio_set(SCLK_PIN, 0);
        delay_us(1);  // SPI时钟下降沿
    }
    return recv;
}
```

#### 🧪 读取 JEDEC ID 示例

```c
void read_jedec_id(void) {
    gpio_set(CS_PIN, 0);            // 拉低CS，开始通信
    spi_transfer(0x9F);             // 发送读取命令
    uint8_t manufacturer = spi_transfer(0x00);
    uint8_t memory_type  = spi_transfer(0x00);
    uint8_t capacity     = spi_transfer(0x00);
    gpio_set(CS_PIN, 1);            // 拉高CS，结束通信

    printf("JEDEC ID: %02X %02X %02X\n", manufacturer, memory_type, capacity);
}
```

---

## 📁 六、项目结构建议（imx6ull\_spi\_demo）

```
imx6ull_spi_demo/
├── Makefile
├── start.S
├── main.c
├── spi_bitbang.c / spi_bitbang.h
├── gpio.c / gpio.h
└── delay.c / delay.h
```

---

## 🧠 七、调试技巧

* 逻辑分析仪观察 MOSI/MISO 时序是否正确
* 确保 SPI 模式匹配 Flash
* 注意 SPI Flash 读取数据前通常需先发一条命令（如 `0x9F`）

---

如果你希望我帮你生成完整裸机工程 `imx6ull_spi_flash_demo`（带启动文件、Makefile、GPIO模拟 SPI 驱动、读取 JEDEC ID 示例），告诉我即可，我可以马上给你一套能编译运行的代码结构。
