要掌握 **GPIO 驱动**，关键是理解 **GPIO 硬件结构、驱动框架、寄存器配置** 以及 **如何通过软件代码控制 GPIO 控制器以驱动外设**（如 LED、蜂鸣器、按键等）。以下将通过嵌入式 Linux 下 GPIO 驱动开发为主线，循序渐进讲解：

---

## ✅ 一、什么是 GPIO？

**GPIO（General Purpose Input/Output）** 是通用输入输出引脚，可以由软件控制为高电平或低电平，或读取其电平状态。

* **输入模式**：读取引脚电平（如按键）
* **输出模式**：驱动电平控制外设（如 LED、继电器）

---

## 🧱 二、GPIO 控制器结构（以 i.MX6ULL 为例）

主控芯片中，GPIO 控制器通过多个寄存器实现对引脚的配置和控制，例如：

| 寄存器           | 功能                        |
| ------------- | ------------------------- |
| GPIOx\_DR     | Data Register，数据寄存器       |
| GPIOx\_GDIR   | Direction Register，方向寄存器  |
| GPIOx\_PSR    | Pad Status Register，状态寄存器 |
| GPIOx\_IMR    | 中断屏蔽寄存器                   |
| GPIOx\_ICR1/2 | 中断配置寄存器                   |

> 如 GPIO1\_IO03 表示 GPIO1 控制器的第3号引脚，对应的是某个具体芯片引脚。

---

## 🧰 三、软件控制 GPIO 的方式（Linux 下）

### 方式 1：通过 sysfs 接口（旧方式，已废弃于 Linux 5.10+）

```bash
# 导出 GPIO 号
echo 123 > /sys/class/gpio/export

# 设置方向
echo out > /sys/class/gpio/gpio123/direction

# 设置高低电平
echo 1 > /sys/class/gpio/gpio123/value
```

---

### 方式 2：通过 `/dev/gpiochipN` + `libgpiod`（推荐）

#### 安装工具：

```bash
sudo apt install libgpiod-dev gpiod
```

#### C 示例代码（输出一个高电平）：

```c
#include <gpiod.h>
#include <stdio.h>

int main() {
    const char *chipname = "gpiochip0";
    struct gpiod_chip *chip;
    struct gpiod_line *line;

    // 打开 GPIO 控制器
    chip = gpiod_chip_open_by_name(chipname);

    // 获取控制器中的某个引脚，如第3号引脚
    line = gpiod_chip_get_line(chip, 3);

    // 设置为输出，并初始化为高电平
    gpiod_line_request_output(line, "mygpio", 1);

    // 控制输出
    gpiod_line_set_value(line, 0);  // 输出低电平
    sleep(1);
    gpiod_line_set_value(line, 1);  // 输出高电平

    // 释放资源
    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}
```

---

## 🔌 四、设备树配置 GPIO（Linux 驱动）

以 LED 灯为例，我们在设备树中定义 GPIO：

```dts
leds {
    compatible = "gpio-leds";

    led0 {
        label = "user_led";
        gpios = <&gpio1 3 GPIO_ACTIVE_LOW>;  // GPIO1_IO03
        default-state = "off";
    };
};
```

* `&gpio1`：表示 GPIO 控制器 1
* `3`：引脚号
* `GPIO_ACTIVE_LOW`：低电平点亮

---

## 🧑‍💻 五、内核驱动中使用 GPIO（平台驱动中调用）

### 驱动中申请 GPIO：

```c
#include <linux/gpio.h>

int gpio = of_get_named_gpio(np, "my-gpio", 0); // 从设备树获取
gpio_request(gpio, "my_gpio");
gpio_direction_output(gpio, 1);  // 设置输出高电平
gpio_set_value(gpio, 0);         // 拉低
```

### 释放 GPIO：

```c
gpio_free(gpio);
```

---

## 🧪 六、典型应用实例

### 1. 控制 LED 灯亮灭（输出）

* 设置为输出
* 输出 0 → 灯亮（GPIO\_ACTIVE\_LOW）

### 2. 读取按键状态（输入）

```c
gpio_direction_input(gpio);
int val = gpio_get_value(gpio);
```

### 3. 中断方式读取按键（中断输入）

```dts
key: gpio-keys {
    compatible = "gpio-keys";
    button@0 {
        label = "user_key";
        gpios = <&gpio1 18 GPIO_ACTIVE_LOW>;
        linux,code = <KEY_ENTER>;
    };
};
```

---

## 📚 七、GPIO 编号计算（重要）

如果没有用设备树，可以通过编号控制 GPIO：

```bash
GPIO编号 = (控制器号 - 1) * 32 + 引脚号
```

例如 `GPIO1_IO03`：

```bash
编号 = (1 - 1) * 32 + 3 = 3
```

---

## 📌 总结重点

| 知识点        | 说明                           |
| ---------- | ---------------------------- |
| GPIO 输入/输出 | 控制电平 or 读取电平状态               |
| libgpiod   | 推荐用户空间控制 GPIO                |
| 设备树配置      | Linux 中 GPIO 驱动绑定方式          |
| 内核驱动 API   | `gpio_request/set_value` 等函数 |
| GPIO 编号计算  | 统一编号或直接用 `gpiochipN`         |

---

如你希望我基于你使用的开发板（如野火 i.MX6ULL）写一个实测 demo，我可以直接给你提供完整工程文件。如果你现在希望使用某种语言（如 C、Shell、Python）操作 GPIO，也可以告诉我，我来提供具体代码。
