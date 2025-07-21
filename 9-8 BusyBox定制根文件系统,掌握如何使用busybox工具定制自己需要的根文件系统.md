好的，下面是第9周课程第8项内容：

---

## 8、BusyBox定制根文件系统

---

### 🎯 课程目标

掌握如何使用BusyBox工具定制适合嵌入式Linux系统的精简根文件系统，提高系统性能和灵活性。

---

### 1. BusyBox简介

* BusyBox是一个集成了众多Unix命令和工具的单个可执行文件，称为“Linux的瑞士军刀”。
* 适合资源有限的嵌入式系统，替代传统的GNU工具集。
* 支持通过配置裁剪功能，生成精简版工具集。

---

### 2. BusyBox的安装与配置流程

#### 1）获取源码

```bash
git clone git://busybox.net/busybox.git
cd busybox
```

#### 2）配置

```bash
make menuconfig
```

* 选择你需要的命令和功能（如shell、ls、ifconfig等）。
* 关闭不需要的选项减少体积。

#### 3）编译

```bash
make CROSS_COMPILE=arm-linux-gnueabihf-
make install CONFIG_PREFIX=./rootfs
```

* `CONFIG_PREFIX`指定安装根目录，会把BusyBox的文件安装到该目录，形成根文件系统框架。

---

### 3. 根文件系统目录结构示例（`CONFIG_PREFIX=rootfs`）

```text
rootfs/
├── bin/           # BusyBox及其它可执行文件
├── sbin/
├── etc/           # 配置文件，如inittab、fstab等
├── dev/           # 设备文件
├── proc/          # 挂载点proc文件系统
├── sys/           # 挂载点sys文件系统
├── tmp/           # 临时文件夹
└── var/           # 变量数据目录
```

---

### 4. 生成设备文件（`dev`目录）

嵌入式系统需要创建设备节点：

```bash
sudo mknod rootfs/dev/console c 5 1
sudo mknod rootfs/dev/null c 1 3
```

---

### 5. 编写简单的`init`脚本

`rootfs/etc/inittab`示例：

```bash
::sysinit:/etc/init.d/rcS
::askfirst:/bin/sh
::shutdown:/bin/umount -a -r
```

`rootfs/etc/init.d/rcS`示例：

```bash
#!/bin/sh
mount -t proc none /proc
mount -t sysfs none /sys
echo "Boot complete"
```

---

### 6. 制作根文件系统镜像

* 使用`cpio`打包为`initramfs`：

```bash
cd rootfs
find . | cpio -o -H newc > ../initramfs.cpio
```

* 或使用`mkfs.jffs2`、`mkfs.ubifs`制作闪存文件系统镜像。

---

### 7. 将根文件系统与内核配合使用

* 通过Bootloader加载内核和根文件系统镜像
* 通过内核参数指定根文件系统位置（如`root=/dev/ram0`或`root=/dev/mtdblock0`）

---

### 8. 优化与裁剪建议

* 只启用必要的命令和功能
* 去掉不必要的支持库和模块
* 减少日志输出和调试信息

---

### 9. 资源推荐

* BusyBox官方网站及文档
* 常用命令配置及示例
* BusyBox源码阅读与自定义扩展

---

需要帮你写一个完整的BusyBox根文件系统制作脚本，或者定制某些命令功能的详细教程吗？
