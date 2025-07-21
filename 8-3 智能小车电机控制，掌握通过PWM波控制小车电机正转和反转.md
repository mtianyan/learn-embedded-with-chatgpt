好的，以下是关于 **智能小车电机控制** 的完整讲解，重点是 **通过 PWM 波控制小车电机正转和反转的原理和实现方法**。

---

## 🏎️ 3、智能小车电机控制：掌握通过 PWM 波控制电机正反转

---

### 🎯 一、电机基本原理

#### 📌 直流电机（DC Motor）特点：

* **正负极接电流 → 电机正转**
* **反接电流 → 电机反转**
* **无电流 → 停止**
* **不同电压占空比 → 控制转速**

---

### 🧰 二、电机驱动芯片（H桥）

#### 常用驱动器（H桥）：

* **L298N**
* **L9110S**
* **TB6612FNG**

#### H桥电路原理：

H桥驱动器内部有 4 个开关，控制电机两端电压方向，从而实现正转、反转和制动。

---

### 🧩 三、PWM 控制原理

#### 什么是 PWM？

PWM（脉冲宽度调制）用于模拟电压控制：

* 占空比高（比如 90%）→ 电机转得快
* 占空比低（比如 30%）→ 电机转得慢

#### 用途：

* 控制电机转速
* 控制舵机角度（非本主题）
* 调光、加热等场景

---

### ⚙️ 四、电机正反转控制逻辑（以 L298N 为例）

L298N 接口说明：

| 引脚  | 功能说明            |
| --- | --------------- |
| IN1 | 控制 A 电机方向       |
| IN2 | 控制 A 电机方向       |
| ENA | A 电机 PWM 输入     |
| VCC | 电机电源（通常 6\~12V） |
| GND | 地               |

控制逻辑表：

| IN1 | IN2 | ENA（PWM） | 结果    |
| --- | --- | -------- | ----- |
| 1   | 0   | PWM      | 正转    |
| 0   | 1   | PWM      | 反转    |
| 0   | 0   | PWM 或 0  | 刹车/空转 |
| 1   | 1   | PWM 或 0  | 刹车    |

---

### 🛠️ 五、STM32 控制示例代码（使用 TIM 生成 PWM）

#### 1. 初始化 TIM 定时器作为 PWM 输出

```c
void TIM3_PWM_Init(uint16_t arr, uint16_t psc)
{
    // 以 TIM3 CH1 为例输出 PWM 到 ENA
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->PSC = psc;
    TIM3->ARR = arr;
    TIM3->CCMR1 |= 6 << 4;  // PWM mode 1
    TIM3->CCER |= 1 << 0;   // Enable CH1
    TIM3->CCR1 = 0;         // 初始占空比为 0
    TIM3->CR1 |= 1;         // 启动定时器
}
```

#### 2. 控制方向 GPIO 初始化

```c
void Motor_GPIO_Init()
{
    // 假设 IN1 接 PB0，IN2 接 PB1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |= (1 << 0*2) | (1 << 1*2);  // 设置 PB0 PB1 为输出
}
```

#### 3. 控制电机函数

```c
void Motor_Set(int dir, uint16_t speed)
{
    if (dir == 1) {
        GPIOB->ODR |= (1 << 0);    // IN1 高
        GPIOB->ODR &= ~(1 << 1);   // IN2 低
    } else if (dir == -1) {
        GPIOB->ODR &= ~(1 << 0);   // IN1 低
        GPIOB->ODR |= (1 << 1);    // IN2 高
    } else {
        GPIOB->ODR &= ~(1 << 0);   // 两个都关
        GPIOB->ODR &= ~(1 << 1);
    }

    TIM3->CCR1 = speed;  // 设置占空比（0 ~ ARR）
}
```

---

### 🧪 六、测试程序示例

```c
int main()
{
    Motor_GPIO_Init();
    TIM3_PWM_Init(1000, 84); // 1kHz PWM（72MHz时钟）

    while (1)
    {
        Motor_Set(1, 500);   // 正转，50%速度
        Delay_ms(2000);
        Motor_Set(-1, 800);  // 反转，80%速度
        Delay_ms(2000);
        Motor_Set(0, 0);     // 停止
        Delay_ms(1000);
    }
}
```

---

### 📌 七、总结

| 控制项  | 实现方式                   |
| ---- | ---------------------- |
| 转速控制 | PWM 占空比调节              |
| 正反转  | 控制 IN1、IN2 电平          |
| 启停   | IN1/IN2 同时低电平或 ENA 为 0 |

---

如需我补充 L298N 实物接线图、CubeMX 配置流程或 FreeRTOS 下电机任务驱动示例，也可以继续告诉我。
