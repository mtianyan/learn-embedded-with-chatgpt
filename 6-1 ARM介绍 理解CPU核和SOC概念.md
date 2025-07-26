当然可以，下面是关于 ARM 以及 SoC 相关概念的清晰介绍，帮助你更好地理解嵌入式系统开发中软件如何驱动硬件。

---

## 一、ARM 介绍

### 1. 什么是 ARM？

ARM（**Advanced RISC Machine**）是一种基于 RISC（**精简指令集计算机**）架构的处理器设计，由英国 ARM 公司（原 Acorn RISC Machine）提出。

> ARM 本身并不制造芯片，而是提供 CPU 的架构和 IP 授权，全球上千家芯片厂商（如 NXP、高通、三星、ST、TI、瑞芯微等）使用 ARM 的 IP 设计并制造符合自己需求的芯片。

---

### 2. ARM 的特点

* **低功耗、低成本**：非常适合嵌入式设备、电池供电设备。
* **高性能**：尤其是近代 Cortex-A 系列已足以驱动 Linux 系统。
* **良好的生态系统**：有完善的编译器（如 GCC、LLVM）、调试器、操作系统（如 Linux、RTOS）等支持。
* **可裁剪性强**：IP 授权机制允许厂商定制不同级别的 CPU 内核（例如加不加 MMU/FPU）。

---

### 3. ARM 的核心分类（Cortex 系列）

ARM Cortex 系列内核按用途分为三大类：

| 类型       | 描述                         | 示例芯片            |
| -------- | -------------------------- | --------------- |
| Cortex-A | 高性能应用处理器，支持 Linux/Android  | i.MX6ULL、RK3288 |
| Cortex-R | 实时处理器，适合对时延敏感的场景（如汽车、工业控制） | TI Hercules     |
| Cortex-M | 面向微控制器，适用于低功耗嵌入式           | STM32、NRF52     |

---

## 二、理解 CPU 核 和 SoC 概念

### 1. CPU 核（Core）

* CPU 核指的是执行指令的核心计算单元。
* 它包括寄存器、ALU（算术逻辑单元）、指令控制器等。
* 一颗芯片可以有一个或多个 CPU 核（单核、双核、四核等）。

---

### 2. SoC（System on Chip，片上系统）

SoC 是一种集成度非常高的芯片，把一个系统的所有功能模块集成到单颗芯片中：

**SoC 通常包含：**

* **CPU 核**（比如 ARM Cortex-A）
* **内存控制器**（DDR 控制器）
* **外设接口**（UART、SPI、I2C、USB、ETH 等）
* **图形加速器 GPU**（可选）
* **音视频编解码器**（如 VPU）
* **电源管理单元**
* **中断控制器、DMA 控制器**

SoC 是嵌入式开发的主要硬件平台。

---

### 3. i.MX6ULL 是什么？

* i.MX6ULL 是 NXP（恩智浦）基于 **ARM Cortex-A7** 核心的 SoC。
* 特点：低功耗、高集成度、支持运行 Linux 操作系统。
* 常用于工业控制、物联网、医疗设备、信息终端等领域。

---

## 三、ARM 芯片生态环境

ARM 芯片生态系统非常完善，包含：

* **编译工具链**：如 arm-none-eabi-gcc，或 arm-linux-gnueabihf-gcc。
* **调试工具**：如 JLink、OpenOCD、GDB。
* **开发板资源**：如树莓派、友善之臂、野火、正点原子等。
* **操作系统支持**：如 u-boot、Linux、FreeRTOS。
* **厂商SDK**：如 NXP 的 MCUXpresso、STM32CubeMX。

---

## 四、总结

| 概念        | 简述                                    |
| --------- | ------------------------------------- |
| ARM       | 一种处理器架构，以低功耗和高效性能为特点                  |
| CPU核      | 实际执行程序指令的处理器核心                        |
| SoC       | 集成了 CPU 核、存储接口、外设接口等模块的一颗“系统芯片”       |
| Cortex 系列 | ARM 提供的核心 IP 类型，分为 A（应用）、R（实时）、M（微控制） |

---

如果你接下来还要学习 **裸机驱动开发、Linux 移植、寄存器控制、外设驱动等内容**，掌握这些基础将非常关键。

需要我继续介绍 i.MX6ULL 的启动流程、内存布局、开发环境搭建吗？

1.课程学习及环境搭建

# 一、课程学习

## 1.学习内容

- ARM核学习
- imx6ull 可以跑Linux
- stm32f103c8t6
- 硬件外设学习 摄像头，传感器

把imx6ull 当成单片机来用

换一款芯片，如何适配，不读死书

## 2.学习方法

- 了解ARM核的工作原理
- 掌握ARM汇编指令及异常处理: 基本不会使用汇编编程,操作系统公司，执行效率高。不可缺少，程序最前面的那部分代码
- 掌握硬件原理图阋读: 硬件工程师,能阅读，能知道被cpu哪个脚控制
- 掌握常用硬件外设工作原理: 产品外设不管哪个公司都是一样的，摄像头厂家也很多，行业标准，基本的工作原理是一样的。看到一个外设知道怎么去驱动他
- 了解芯片控制器相关寄存器设置: 开关做不同的设置，完成不同的操作

# 二、ARM指令模拟器环境搭建

## 1.keil软件

KEIL是公司的名称，有时候也指KEIL公司的所有软件开发工具，目前2005年Keil由ARM公司收购，成为ARM的公司之一。

MDK (Microcontroller Development Kit),也称MPK-ARM、 KEIL MDK、 RealView MDK、 KEILFor ARM，都是同一个东西。ARM公司现在统一使用MDK-ARM的称呼，MDK的设备数据库中有很多厂商的芯片，是专为微控制器开发的工具，为满足基于MCU进行嵌入式软件开发的工程师需求而设计支持ARM7，ARM9，Cortex-M4/M3/M1，Cortex-RO/R3/R4等ARM微控制器内核。

MCU（Microcontroller Unit，微控制器单元），又称单片机或微控制器，是一种将​​中央处理器（CPU）、存储器、定时器/计数器及多种输入/输出接口（如USB、ADC、UART等）集成在单一芯片上的微型计算机系统​​。

https://www.keil.com/download/product/

![](http://cdn.pic.funpython.cn/image/202507261937844.png)




## 2.激活软件
## 3.Legacy support

老的arm 7 arm9 不支持

MDK Version 5 uses Software Packs to support a microcontroller device and to use middleware. Tomaintain backward compatibility with MDK Version 4 you may install Legacy Support. This mightbe necessary for two reasons:
.To maintain projects created with MDK Version 4 without migrating to Software Packs.
To use older devices that are not supported by a Device Family Pack.
MDK版本5使用软件包来支持微控制器设备和使用中间件。要保持与MDK版本4的向后兼容性，您可以安装旧版支持。这可能是必要的，原因有两个:
维护使用MDK版本4创建的项目，而无需迁移到软件包
使用设备系列包不支持的旧设备

https://www2.keil.com/mdk5/legacy

![](http://cdn.pic.funpython.cn/image/202507262252148.png)

![](http://cdn.pic.funpython.cn/image/202507262252006.png)

这两个安装包需要安装在一个路径下

![](http://cdn.pic.funpython.cn/image/202507262258494.png)


# 第1章芯片产业链及ARM核介绍


# 2.ARM核介绍

一、芯片产业链

- 1.CPU核

1.CPU核
CPU又叫中央处理器，其主要功能是进行运算和逻辑运算，内部结构大概可以分为控制单元、算术逻辑单元和存储单元等几个部分。按照其处理信息的字长可以分为:八位微处理器、十六位微处理器、三十二位微处理器以及六十四位微处理器等等。

除法运算很特殊，cpu一般无法直接除法。因为除不尽

一次性可以处理多少长度的数据

![](http://cdn.pic.funpython.cn/image/202507262302279.png)

### clock 单元，人的心脏，时钟信号(电压信号按频率) cpu主频 2.6ghz

外围电压时钟信号 改大一点点可以超频运行

![](http://cdn.pic.funpython.cn/image/202507262304340.png)

读取寄存器中的机器码，通过预取电路

cpu 内部很多寄存器。高速cache->拿到数据和指令

ghz 内存1333mhz

cpu ghz 火箭拉内存乌龟

高速缓存比内存快很多。for循环指令固定


### CPU厂家主要工作:

机器码设计 0101 arm 和 intel 不一样

java编译后是字节码，java虚拟机把字节码翻译成机器码

主频 

高速缓存(cache)

多核集成

硬件浮点运算

软浮点 1.2 + 1.3 翻译成了很多条指令，如果支持硬件浮点，一条指令既可以

数据运算

功耗 电脑功耗高

CISC: Complex Instruction Set Computer，复杂指令集计算机: 

机器码指令宽度不固定，一条指令对应精简指令10条

RISC:Reduced Instruction Set Computer，精简指令集计算机

机器码指令宽度固定

### (1)ARM

ARM是Advanced RIsc Machines的缩写，它是一家微处理器行业的知名企业，该企业设计了大量高性能、廉价、低功耗的RISC(精简指令集)处理器ARM 公司的特点是只设计芯片，而不生产。它将技术授权给半导体厂商，并提供服务。

![](http://cdn.pic.funpython.cn/image/202507262315370.png)

芯片生产技术很高，arm把技术卖给别人。真正的cpu核设计师很难的。

靠授权赚钱，一片芯片提成几美分，聪明的大脑

国外只做自己的部分，不做全链

华为海思也可以设计，制造需要光刻机

ARM将其芯片设计技术(内核、体系扩展、微处理器和系统芯片方案)授权给Intel，SamsungTI，高通(Qualcomm)，意法半导体等半导体制造商，这些厂商拿到ARM内核以后，再设计外围的各种控制器，和ARM核整合成一块SOC芯片

arm不关心外围如摄像头，显示屏等，只关心cpu核指令，计算








### (2)MIPS

(2)MIPS
MIPS(Million Instructions Per Second)技术公司是美国一家设计制造高性能、高档次及嵌入式32位和64位处理器的厂商，在RISC处理器方面占有重要地位。
MIPS的商业模式和ARM相似，也是研发处理器内核，将知识产权授权给其他公司，我国的国产处理器厂商龙芯就是获得MIPS32和MIPS64架构的授权，借此开发龙芯CPU。




### (3)PowerPc

PowerPC (英语:Performance Optimization With Enhanced RIsc-Performance
Computing，有时简称PPC)是一种精简指令集(RISC)架构的中央处理器(CPU)，其基本的设计源自IBM的POWER(Performance Optimized With Enhanced RIsC);


### (4)Intel

X86架构是复杂指令集工主要用于PC产业。

### （5）RISC-V

RISC-V(读作“RISC-FIVE”)是基于精简指令集计算(RISC)原理建立的开放指令集架构(ISA)，V表示为第五代RISC(精简指令集计算机),表示此前已经有四代RISC处理器原型芯片。每一代RISC处理器都是在同一人带领下完成，那就是加州大学伯克利分校的David A.Patterson教授。与大多数ISA相反，RISC-V ISA可以免费地用于所有希望的设备中，允许任何人设计、制造和销售RISC-V芯片和软件。

阿里平头哥用了这个，开源很重要

##  2.SOC芯片

2.SOC芯片
SOc(System On chip:CPU核 +外围控制器),片上系统，即在一块芯片上集成一整个信息处理系统，简单来说 SoC芯片是在中央处理器CPU的基础上扩展专用接口的超大规模集成电路，是智能设备的“大脑”。


![](http://cdn.pic.funpython.cn/image/202507262326087.png)

一般称呼的手机cpu就是soc了，电脑上cpu就是cpu，控制器
是南桥 / 北桥芯片组，或pch 平台控制器中心

### 📱 手机：SoC（System on Chip）

* 手机用的是 **SoC**，中文叫“系统级芯片”。
* SoC 是**集成度极高的芯片**，把 CPU、GPU、DSP、NPU、基带（通信模块）、Wi-Fi、蓝牙、电源管理 等都集成到一颗芯片里。
* 代表例子：

  * 高通 Snapdragon（骁龙）
  * 苹果 A 系列（A17 等）
  * 联发科 天玑
  * 华为 麒麟

---

### 💻 电脑：CPU + 其他组件

* 电脑的架构更“分离”，不是一颗芯片搞定一切，而是：

  * **CPU**：中央处理器（处理通用计算）
  * **GPU**：显卡（图形运算）
  * **内存控制器**：大多数已集成到 CPU 里
  * **南桥 / 北桥芯片组**（旧时代的概念）
  * **PCH（平台控制器中心）**：现在 Intel/AMD 用来替代南桥，处理 USB、音频、SATA 等 I/O


lcd 显示屏 csi 控制摄像头

华为，高通，设计soc，cpu一样，其他控制器不同

## (1)主流厂家

德州仪器(TI)
高通(Qualcomm)
三星(Samsung)
恩智浦(NXP)
全志(Allwinner Technology)
华为海思(Hisilicon)
联发科(MTK)
瑞星薇(rockchip)

## (2)产品解决方案

手机解决方案
平板解决方案
智能电视解决方案




## 3.产品

3.产品

特斯拉
小米
华为
格力
大疆
飞利浦


芯片公司和产品公司工作，工资多可以去芯片公司，产品公司可以创业

# 1-3ARM核发展介绍

![](http://cdn.pic.funpython.cn/image/202507262353889.png)


应用就是手机这类， 实时处理是工业领域，单片机

课程里用到的是cortex-a7

![](http://cdn.pic.funpython.cn/image/202507262354439.png)


ARM公司在经典处理器ARM11以后的产品改用Cortex命名，并分成A、R和M三类，旨在为各种不同的市场提供服务。Cortex系列属于ARMv7架构，由于应用领域不同，基于v7架构的Cortex处理器系列所采用的技术也不相同，基于V7A的称为Cortex-A系列，基于V7R的称为Cortex-R系列，基于v7M的称为Cortex-M系列。

![](http://cdn.pic.funpython.cn/image/202507262354175.png)


armv8 完全兼容armv7

![](http://cdn.pic.funpython.cn/image/202507262356116.png)

FPU 是“浮点运算单元”的统称，
VFP 是 ARM 架构中的一种具体 FPU 实现。

## (1)VFP
VFP(Vector Floating-point Coprocessor for ARM)向量浮点运算单元(协处理器)。它提供低成本的单精度和倍精度浮点运算能力，并完全相容于ANSI/IEEE Std 754-1985 二进制浮点算数标准。VFP 提供大多数适用于浮点运算的应用，例如PDA、I智慧手机、语音压缩与解压、3D图像以及数位音效、打印机、机上盒，和汽车应用等。

## (2)Jazelle
Jazelle是ARM体系结构的一种相关技术，用于在处理器指令层次对JAVA加速。ARM的Jazelle技术使Java加速得到比基于软件的Java虚拟机(JVM)高得多的性能，和同等的非java加速核相比功耗降低80%.

cpu核直接解析部分字节码

## (3)Thumb
表示ARM处理器可以工作在Thumb状态，执行Thumb指令集。ARM指令集是32bit的指令集，在Thumb状态执行的指令集是16bit的。Thumb指令集不是完整的指令集，它是ARM指令集的子集。但是Thumb指令具有更高的代码密度，即占用存储空间小，仅为ARM代码规格的65%，但其性能却下降的很少。所以，Thumb指令集使ARM处理器能应用到有限的存储带宽，并且，代码密度要求很高的嵌入式系统中去。
Thumb-2 是 Thumb 指令集的一项主要增强功能，并且由 ARMv6T2 和 ARMV7M体系结构定义。Thumb-2 提供了几乎与 ARM 指令集完全一样的功能。 它兼有16 位和 32 位指令，并可检索与ARM 类似的性能，但其代码密度与 Thumb 代码类似。

单片机上面运行内存是几十kb，代码体积就变重要了

## (4)TrustZone

TrustZone是ARM针对消费电子设备设计的一种硬件架构，其目的是为消费电子产品构建一个安全框架来抵御各种可能的攻击。

TrustZone在概念上将SoC的硬件和软件资源划分为安全(Secure World)和非安全(NormalWorld)两个世界，所有需要保密的操作在安全世界执行(如指纹识别、密码处理、数据加解密、安全认证等)，其余操作在非安全世界执行(如用户操作系统、各种应用程序等)。

![](http://cdn.pic.funpython.cn/image/202507270003166.png)

木马程序没法进入安全世界。芯片公司才知道如何进入

## (5)SIMD
SIMD，即 single instruction multiple data，单指令流多数据流，也就是说一次运算指令可以执行多个数据流，从而提高程序的运算速度，实质是通过 数据并行 来提高执行效率

![](http://cdn.pic.funpython.cn/image/202507270005274.png)

数据并行直接相加

## (6)NEON

ARMv7之后，将SIMD升级为 NEON技术 相当于**扩展了浮点运算向量表**有一个VFS的二维向量表，将数据存放到这个表中，cpu可以一次性取某个区域进行执行，**NEON就是SIMD的升级 相当于将上面SIMD执行指令的表格长度与宽度进行扩展，提升了数据集的压缩算法**。 NENO可以进行指令扩展来实现相关功能，但我们一般不使用，如果做一些GPU相关的工作就需要利用NENO的浮点运算特性。 可用于加速多媒体和信号处理算法(如视频编码/解码)、2D/3D图形、游戏、音频和语音处理、图像处理技术、电话和声音合成，其性能至少为ARMv5的3倍，为ARMV6 SIMD性能的两倍 在SIMD的基础上提升了两倍效率 所以运算速度的加快不是单纯的提升CPU的频率 通过这两个技术提升指令执行的方式，还有其他的方法(比如增加二级缓存)




















