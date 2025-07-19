好的，我们继续，进入 Linux **进程管理与服务管理命令**，这部分是运维和系统调优的基础。

---

## ⚙️ 第5部分：进程管理与服务管理命令

---

### 一、进程管理命令

| 命令             | 功能描述             |
| -------------- | ---------------- |
| `ps`           | 查看当前运行的进程        |
| `top` / `htop` | 实时动态查看系统进程和资源使用  |
| `pgrep`        | 根据名字查找进程ID       |
| `pidof`        | 查找指定程序的进程号       |
| `kill`         | 发送信号杀死进程         |
| `killall`      | 杀死指定名称的所有进程      |
| `nice`         | 设置进程优先级          |
| `renice`       | 修改已运行进程的优先级      |
| `jobs`         | 查看当前 shell 的后台任务 |
| `fg` / `bg`    | 将后台任务切换到前台/后台    |

---

### 常用示例

```bash
# 查看所有进程
ps aux

# 实时查看进程资源占用
top

# 进阶版（需安装）
htop

# 查找 nginx 进程ID
pgrep nginx

# 结束进程
kill <PID>

# 强制杀死进程
kill -9 <PID>

# 根据名称杀死所有 nginx 进程
killall nginx

# 启动一个进程并设置优先级（优先级-20最高，19最低）
nice -n 10 ./my_program

# 修改已运行进程优先级
renice -n 5 -p <PID>

# 查看当前 shell 的后台任务
jobs

# 将后台任务切换到前台
fg %1

# 将任务放入后台运行
bg %1
```

---

### 二、服务管理命令（Systemd为主）

| 命令                                    | 功能描述   |
| ------------------------------------- | ------ |
| `systemctl status <service>`          | 查看服务状态 |
| `systemctl start <service>`           | 启动服务   |
| `systemctl stop <service>`            | 停止服务   |
| `systemctl restart <service>`         | 重启服务   |
| `systemctl enable <service>`          | 开机自启   |
| `systemctl disable <service>`         | 取消开机自启 |
| `systemctl list-units --type=service` | 查看所有服务 |

---

### 常用示例

```bash
# 查看 nginx 服务状态
sudo systemctl status nginx

# 启动 nginx 服务
sudo systemctl start nginx

# 停止 nginx 服务
sudo systemctl stop nginx

# 重启 nginx 服务
sudo systemctl restart nginx

# 设置 nginx 开机启动
sudo systemctl enable nginx

# 取消开机启动
sudo systemctl disable nginx

# 查看所有正在运行的服务
systemctl list-units --type=service --state=running
```

---

## ✅ 实战练习

1. 使用 `ps aux` 找出自己启动的进程
2. 用 `top` 观察 CPU 和内存使用情况
3. 查找并杀死一个指定名称的进程（例如 `my_app`）
4. 启动一个服务（如 nginx），查看状态，设置开机启动
5. 停止服务并取消开机启动

---

需要我帮你整理成 Markdown 笔记吗？或者你想了解更底层的信号、进程调度等高级知识？
