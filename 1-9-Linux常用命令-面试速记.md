明白了！下面是**面向企业笔试和面试的 Linux 常用命令默写清单**，涵盖企业常考的文件管理、权限、用户管理、网络管理、磁盘管理、进程管理等方面，重点考察命令的正确写法和基本用法。

---

# 📝 企业笔试 & 面试 Linux 常用命令默写清单

---

## 一、文件和目录操作

| 需求描述            | 常用命令（示范写法）                  |
| --------------- | --------------------------- |
| 列出当前目录文件（长格式显示） | `ls -l`                     |
| 显示包括隐藏文件        | `ls -a`                     |
| 递归列出目录          | `ls -R`                     |
| 创建目录            | `mkdir dirname`             |
| 创建多级目录          | `mkdir -p /path/to/dir`     |
| 删除空目录           | `rmdir dirname`             |
| 删除目录及内容         | `rm -rf dirname`            |
| 复制文件            | `cp source dest`            |
| 复制目录及其内容        | `cp -r sourcedir destdir`   |
| 移动或重命名文件        | `mv oldname newname`        |
| 显示文件内容（分页）      | `less filename`             |
| 显示文件最后10行       | `tail -n 10 filename`       |
| 实时查看文件增长        | `tail -f filename`          |
| 查找文件            | `find /path -name filename` |
| 查找包含某文本的文件      | `grep "text" filename`      |
| 查找当前目录及子目录中的文件  | `find . -name "*.log"`      |

---

## 二、文件权限和所有权

| 需求描述      | 常用命令（示范写法）                  |
| --------- | --------------------------- |
| 修改权限（数字法） | `chmod 755 filename`        |
| 修改权限（符号法） | `chmod u+x filename`        |
| 修改文件属主    | `chown user filename`       |
| 修改文件属组    | `chown :group filename`     |
| 修改文件属主及属组 | `chown user:group filename` |
| 查看权限      | `ls -l filename`            |

---

## 三、用户与用户组管理

| 需求描述        | 常用命令（示范写法）                            |
| ----------- | ------------------------------------- |
| 查看当前用户名     | `whoami`                              |
| 查看用户详细信息    | `id username`                         |
| 添加用户        | `sudo adduser username`               |
| 删除用户（含家目录）  | `sudo deluser --remove-home username` |
| 修改用户密码      | `passwd username`                     |
| 添加组         | `sudo groupadd groupname`             |
| 删除组         | `sudo groupdel groupname`             |
| 用户加入组       | `sudo usermod -aG groupname username` |
| 查看用户所属组     | `groups username`                     |
| 切换用户        | `su - username`                       |
| 以其他用户权限运行命令 | `sudo -u username command`            |

---

## 四、网络管理

| 需求描述        | 常用命令（示范写法）                        |
| ----------- | --------------------------------- |
| 查看所有网络接口及IP | `ip addr show`                    |
| 测试网络连通      | `ping -c 4 www.google.com`        |
| 路由跟踪        | `traceroute www.google.com`       |
| 查看监听端口      | `ss -tuln`                        |
| 查看所有网络连接    | `netstat -tulnp`                  |
| DNS 查询      | `nslookup www.baidu.com`          |
| 发送 HTTP 请求  | `curl -I https://www.example.com` |
| 下载文件        | `wget https://example.com/file`   |

---

## 五、磁盘管理

| 需求描述        | 常用命令（示范写法）             |
| ----------- | ---------------------- |
| 查看磁盘及分区信息   | `lsblk`                |
| 查看磁盘空间使用    | `df -h`                |
| 查看目录大小      | `du -sh /path/to/dir`  |
| 挂载分区        | `mount /dev/sda1 /mnt` |
| 卸载分区        | `umount /mnt`          |
| 查看分区UUID    | `blkid /dev/sda1`      |
| 查看磁盘分区表     | `fdisk -l /dev/sda`    |
| 格式化分区为 ext4 | `mkfs.ext4 /dev/sda1`  |

---

## 六、进程管理与服务

| 需求描述      | 常用命令（示范写法）                      |
| --------- | ------------------------------- |
| 查看所有进程    | `ps aux`                        |
| 实时查看进程    | `top`                           |
| 查找进程ID    | `pgrep processname`             |
| 结束进程      | `kill PID`                      |
| 强制结束进程    | `kill -9 PID`                   |
| 查看后台任务    | `jobs`                          |
| 切换后台任务到前台 | `fg %1`                         |
| 查看服务状态    | `systemctl status servicename`  |
| 启动服务      | `systemctl start servicename`   |
| 停止服务      | `systemctl stop servicename`    |
| 设置服务开机启动  | `systemctl enable servicename`  |
| 取消服务开机启动  | `systemctl disable servicename` |

---

## 七、文本处理（简要）

| 需求描述          | 常用命令（示范写法）                      |
| ------------- | ------------------------------- |
| 查找文件中包含某字符串的行 | `grep "text" filename`          |
| 按列提取文本字段      | `awk '{print $1, $3}' file.txt` |
| 替换文本内容        | `sed 's/old/new/g' file.txt`    |
| 统计行数          | `wc -l filename`                |

---

# 附加建议

* **写出正确的命令选项**是企业面试重点（如 `-r` `-f` `-a` `-n` `-h` 等）
* **理解命令作用及场景**，不仅仅是死记硬背
* **能手写简单的命令组合**，如查找并删除、统计并排序等

---

需要的话，我可以帮你整理成**可打印的笔试复习卡片**或**markdown 格式速查表**，方便记忆和练习。或者帮你做一些典型笔试题和答案解析。你看呢？
