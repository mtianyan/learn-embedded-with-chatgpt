**1-Wire 总线通信原理与温度采集（以 DS18B20 为例）**

---

### 📌 一、1-Wire 简介

1-Wire（单总线）是一种**单根信号线 + 地线**即可完成数据通信的串行总线通信协议，由 Dallas Semiconductor（后被 Maxim 收购）开发。具有如下特点：

* **单根数据线**（即“1-Wire”）
* 支持**多个设备并联**
* **主设备主动发起通信**（轮询式）
* 数据线通常接一个**上拉电阻**（4.7kΩ）
* **半双工通信**

---

### 🔧 二、硬件连接（以 DS18B20 为例）

| 引脚  | 说明  | 连接方式      |
| --- | --- | --------- |
| VDD | 电源  | 可接3.3V    |
| GND | 地   | 接地        |
| DQ  | 数据线 | GPIO + 上拉 |

---

### 📖 三、通信时序基础

通信流程通常包括：

1. **复位脉冲（Reset Pulse）**

   * 主机将数据线拉低 ≥480μs
   * 从机回应一个 60-240μs 的低电平脉冲（Presence Pulse）

2. **读写时序**

   * 写 1：拉低数据线 1\~15μs 后释放
   * 写 0：拉低数据线 ≥60μs
   * 读位：拉低1μs后释放，15μs 时读取数据线电平

3. **CRC 校验**：用于校验数据有效性

---

### 🧠 四、1-Wire 协议常用命令

* `0x33`：读取 ROM（仅单个设备）
* `0xCC`：跳过 ROM（Skip ROM，广播命令）
* `0x44`：温度转换（Convert T）
* `0xBE`：读取温度数据（Read Scratchpad）

---

### 💡 五、DS18B20 温度读取流程

```text
主机复位
↓
从机应答
↓
主机发送 0xCC（跳过 ROM）
↓
主机发送 0x44（触发温度转换）
↓
等待转换完成（最大750ms）
↓
主机再次复位 + 应答
↓
主机发送 0xCC（跳过 ROM）
↓
主机发送 0xBE（读取数据）
↓
从机发送 9字节 Scratchpad 数据
```

---

### 🧪 六、裸机实现的关键代码逻辑（伪代码）

```c
void onewire_reset(void) {
    set_gpio_output();
    pull_gpio_low();
    delay_us(500);
    set_gpio_input();
    delay_us(60);
    if (gpio_read() == 0) { device_present = 1; }
    delay_us(420);
}

void write_byte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        write_bit(byte & 0x01);
        byte >>= 1;
    }
}

uint8_t read_byte(void) {
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++) {
        byte |= (read_bit() << i);
    }
    return byte;
}

float ds18b20_read_temp(void) {
    onewire_reset();
    write_byte(0xCC); // Skip ROM
    write_byte(0x44); // Convert T
    delay_ms(750);    // Wait conversion
    onewire_reset();
    write_byte(0xCC); // Skip ROM
    write_byte(0xBE); // Read Scratchpad
    uint8_t lsb = read_byte();
    uint8_t msb = read_byte();
    return ((msb << 8) | lsb) * 0.0625;
}
```

---

### 📦 七、项目结构建议

```
1wire_temp_demo/
├── Makefile
├── start.S
├── main.c
├── onewire.c / onewire.h
├── gpio.c / gpio.h
└── delay.c / delay.h
```

---

### 🔧 八、调试技巧

* **逻辑分析仪**可以辅助观察时序是否正确
* 检查上拉电阻是否正确连接
* 若多个 DS18B20，共享一根总线，可使用 `0x33/0x55` 指令读取唯一 ROM 码再区分设备

---

需要我帮你写出完整的 `imx6ull_1wire_demo` 工程代码结构（含 Makefile、启动文件、main.c、1-wire 驱动）吗？可以立即生成。
