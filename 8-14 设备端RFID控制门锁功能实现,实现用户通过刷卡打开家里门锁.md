好的，下面是第8+周第2项课程内容：

---

## 设备端RFID控制门锁功能实现

---

### 🎯 课程目标

掌握基于STM32单片机与RFID模块的通信和控制，完成刷卡识别并控制门锁开关，实现用户刷卡打开家里门锁的功能。

---

### 1. RFID模块简介

* 常用模块：如 MFRC522（SPI通信）、RC522等
* 工作频率：13.56MHz（高频）
* 主要功能：读取卡片唯一ID（UID）、写读数据
* 通信接口：SPI、UART，主流为SPI

---

### 2. 硬件连接

| RFID模块引脚 | STM32引脚          | 说明       |
| -------- | ---------------- | -------- |
| MOSI     | SPI MOSI (如 PA7) | 主机发送数据线  |
| MISO     | SPI MISO (如 PA6) | 主机接收数据线  |
| SCK      | SPI时钟线 (如 PA5)   | SPI时钟    |
| NSS      | SPI片选线 (如 PA4)   | 选择RFID模块 |
| RST      | 复位线 (如 PC4)      | 模块复位     |
| GND      | GND              | 地线       |
| VCC      | 3.3V             | 电源       |

---

### 3. RFID刷卡流程

1. **初始化模块**
   配置SPI接口，初始化RFID模块。

2. **检测卡片**
   轮询检测是否有卡片靠近模块。

3. **读取卡片UID**
   读取卡片唯一ID号。

4. **校验卡号**
   MCU内部维护合法卡号列表，进行比对。

5. **开锁控制**
   校验通过，控制继电器或电机驱动门锁打开。

---

### 4. RFID核心命令简述

| 命令              | 作用      | 说明      |
| --------------- | ------- | ------- |
| PICC\_REQIDL    | 请求检测空闲卡 | 探测卡片存在  |
| PICC\_ANTICOLL  | 防冲撞     | 读取卡UID  |
| PICC\_AUTHENT1A | 验证密钥A   | 读写操作前验证 |
| PICC\_READ      | 读取数据块   | 读卡数据    |
| PICC\_WRITE     | 写数据块    | 写卡数据    |

---

### 5. 代码示例（简化版，基于HAL库）

```c
#include "spi.h"
#include "gpio.h"

// 初始化MFRC522
void MFRC522_Init(void)
{
    // SPI和GPIO初始化
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
    // 其他寄存器配置
}

// 读取卡片UID
uint8_t MFRC522_ReadUID(uint8_t *uid)
{
    uint8_t status;
    uint8_t str[MAX_LEN];

    status = MFRC522_Request(PICC_REQIDL, str);
    if (status == MI_OK)
    {
        status = MFRC522_AntiColl(str);
        if (status == MI_OK)
        {
            for (int i = 0; i < 4; i++)
                uid[i] = str[i];
            return 1; // 读取成功
        }
    }
    return 0; // 失败
}

// 主程序示例
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI1_Init();

    MFRC522_Init();

    uint8_t card_uid[4];
    while (1)
    {
        if (MFRC522_ReadUID(card_uid))
        {
            if (IsValidCard(card_uid)) // 验证卡号
            {
                DoorLock_Control(1); // 开锁
                HAL_Delay(5000);
                DoorLock_Control(0); // 关锁
            }
        }
        HAL_Delay(200);
    }
}
```

---

### 6. 关键点总结

* SPI总线的初始化及正确连接
* RFID模块的寄存器配置与命令流程
* 卡号识别与比对逻辑
* 门锁驱动（继电器或电机）控制
* 异常处理（无卡、识别失败、超时等）

---

如果需要，我可以帮你写更详细的MFRC522驱动代码、示例工程，或者配套的卡号管理系统代码。需要吗？
