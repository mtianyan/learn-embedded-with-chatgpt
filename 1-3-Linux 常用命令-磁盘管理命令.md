好的，进入 Linux **磁盘管理命令** 部分！这部分帮助你了解磁盘设备、分区、挂载以及使用情况监控。

---

## 💽 第4部分：磁盘管理命令

---

### 📋 常用磁盘管理命令总览

| 命令                         | 功能描述               |
| -------------------------- | ------------------ |
| `lsblk`                    | 列出块设备信息，显示磁盘及分区    |
| `fdisk`                    | 磁盘分区工具（交互式）        |
| `parted`                   | 分区管理工具（支持GPT等高级功能） |
| `df`                       | 查看磁盘空间使用情况         |
| `du`                       | 查看文件/目录磁盘占用大小      |
| `mount`                    | 挂载磁盘分区             |
| `umount`                   | 卸载挂载的磁盘            |
| `blkid`                    | 查看磁盘分区的 UUID 和类型   |
| `ls -l /dev/disk/by-uuid/` | 根据 UUID 查找磁盘设备     |
| `tune2fs`                  | 调整ext文件系统参数        |
| `mkfs`                     | 格式化磁盘分区            |

---

### 1. 查看磁盘和分区信息

```bash
lsblk

# 输出示例：
# NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
# sda      8:0    0 238.5G  0 disk 
# ├─sda1   8:1    0   512M  0 part /boot
# ├─sda2   8:2    0 237.5G  0 part /
# └─sda3   8:3    0   512M  0 part [SWAP]
```

---

### 2. 查看磁盘空间使用情况

```bash
df -h

# 参数说明：
# -h ：以人类可读方式显示（GB, MB）
```

---

### 3. 查看目录/文件占用磁盘大小

```bash
du -sh /var/log

# 参数说明：
# -s ：汇总总大小
# -h ：人类可读
```

---

### 4. 挂载和卸载磁盘分区

```bash
sudo mount /dev/sda1 /mnt

# 卸载
sudo umount /mnt
```

---

### 5. 查看磁盘分区详细信息

```bash
sudo fdisk -l /dev/sda
```

---

### 6. 格式化磁盘分区（示例格式化为 ext4）

⚠️ 格式化会清空数据，操作前请确认！

```bash
sudo mkfs.ext4 /dev/sda3
```

---

### 7. 使用 parted 进行分区（交互式示例）

```bash
sudo parted /dev/sda
# 进入 parted 交互模式后，可用命令：
# (parted) print         # 查看分区表
# (parted) mkpart primary ext4 1MiB 100%  # 创建新分区
# (parted) quit          # 退出
```

---

### 8. 查看分区 UUID

```bash
sudo blkid /dev/sda1
```

---

## ✅ 实战练习

1. 使用 `lsblk` 查看你的磁盘和分区
2. 使用 `df -h` 查看磁盘空间使用情况
3. 查看某目录磁盘占用情况，例如 `du -sh ~/Documents`
4. 挂载一个分区到 `/mnt`，然后卸载它
5. 格式化一个磁盘分区（虚拟机测试环境，避免重要数据）
6. 使用 `fdisk -l` 查看磁盘分区详情

---

需要我帮你整理这部分命令的详细示例文档吗？或者你想直接进入其他管理领域（比如进程管理、服务管理）？
