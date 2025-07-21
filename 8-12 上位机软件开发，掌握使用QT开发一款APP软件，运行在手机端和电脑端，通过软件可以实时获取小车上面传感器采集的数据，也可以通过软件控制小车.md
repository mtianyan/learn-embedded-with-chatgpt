✅ 以下是 **第 12 项课程内容：上位机软件开发（QT 跨平台 APP）** 的详细介绍与实操指导：

---

## **12、上位机软件开发 —— 使用 QT 实现跨平台小车控制与数据监测**

---

### 🎯 课程目标

* 掌握使用 **Qt 框架** 开发跨平台 GUI 应用（支持 Windows、Linux、Android、iOS）
* 实现通过串口或网络实时获取小车传感器数据
* 实现通过软件界面发送控制指令，实现对小车运动的远程控制

---

### 🛠️ 技术栈与工具

| 技术/工具          | 说明                    |
| -------------- | --------------------- |
| Qt 5/6         | 跨平台应用框架，支持 GUI、网络、串口等 |
| Qt Creator     | Qt 官方集成开发环境           |
| C++            | 主开发语言                 |
| Qt Serial Port | 串口通信模块                |
| Qt Network     | TCP/UDP 网络通信支持        |
| QML（可选）        | 声明式 UI 设计，可增强界面交互体验   |

---

### 🧩 开发步骤

#### 1. 环境搭建

* 下载并安装 Qt SDK（含 Qt Creator）
* 配置对应平台的编译工具链（MinGW、MSVC、Android SDK 等）

#### 2. UI 设计

* 使用 Qt Designer 设计控制面板界面

  * 按钮（前进、后退、左转、右转、停止）
  * 数据显示框（温湿度、距离、速度等实时数据）
  * 状态指示灯/图标

#### 3. 通信实现

* **串口通信**（控制小车与上位机物理连接）

  * 打开串口
  * 读写数据
  * 处理数据解析与指令发送

* **网络通信**（WiFi 控制）

  * TCP 客户端/服务器架构
  * 发送控制命令
  * 接收传感器数据

#### 4. 数据处理与显示

* 解析传感器数据（如温湿度、距离、状态）
* 更新界面显示内容
* 响应用户操作，发送控制指令

---

### 🧑‍💻 示例代码片段（串口通信）

```cpp
// 打开串口
serial = new QSerialPort(this);
serial->setPortName("COM3");
serial->setBaudRate(QSerialPort::Baud115200);
serial->open(QIODevice::ReadWrite);

// 发送控制指令
void MainWindow::sendCommand(const QString &cmd)
{
    if (serial->isOpen())
    {
        QByteArray data = cmd.toUtf8();
        serial->write(data);
    }
}

// 读取串口数据
void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    // 解析传感器数据，更新UI
}
```

---

### 📱 手机端部署

* Qt 支持 Android 和 iOS 应用打包
* 配置移动设备调试环境
* 移动端 UI 可用 QML 优化交互体验

---

### 🎨 UI 示例设计建议

* 左侧为控制按钮区，按钮简洁明了
* 右侧为数据展示区，图表和文本混合显示
* 状态栏显示当前连接状态和错误提示

---

### 🚀 项目拓展方向

* 通过 MQTT 或 WebSocket 实现云端数据传输和控制
* 增加用户登录、权限管理等功能
* 支持多台小车同时控制和管理
* 增加轨迹回放、历史数据分析功能

---

### 需要帮忙的内容？

* Qt 项目初始化模板
* 串口通信完整示例
* TCP/IP 网络通信示例
* 移动端 Qt QML 界面设计
* 小车控制协议设计

告诉我，我可以帮你写代码或设计方案！
