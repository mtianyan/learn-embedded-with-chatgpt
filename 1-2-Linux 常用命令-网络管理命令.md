## 🌐 第 3 部分：网络管理命令

---

### 📋 常用网络命令概览

| 命令                 | 功能描述                     |
| ------------------ | ------------------------ |
| `ip`               | 网络接口配置和查看（替代老的 ifconfig） |
| `ifconfig`         | 查看/配置网络接口（部分系统不推荐用）      |
| `ping`             | 测试网络连通性                  |
| `traceroute`       | 路由跟踪                     |
| `netstat`          | 查看网络连接、端口、路由表            |
| `ss`               | 查看套接字统计，比 netstat 更现代    |
| `nslookup` / `dig` | DNS 查询                   |
| `curl` / `wget`    | 网络请求工具                   |
| `route`            | 路由表管理（旧版命令）              |
| `tcpdump`          | 抓包分析网络流量                 |
| `nmcli`            | NetworkManager 命令行工具     |

---

### 1. 查看网络接口状态与IP信息

```bash
ip addr show                 # 显示所有接口及IP
ip link show                 # 显示所有网络接口状态（up/down）
```

示例：

```bash
ip addr show eth0

# 输出示例：
# 2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 ...
#     inet 192.168.1.100/24 brd 192.168.1.255 scope global eth0
```

---

### 2. 配置 IP 地址（临时生效）

```bash
sudo ip addr add 192.168.1.123/24 dev eth0   # 添加IP
sudo ip addr del 192.168.1.123/24 dev eth0   # 删除IP
```

---

### 3. 测试连通性

```bash
ping www.google.com            # 测试网络连通（CTRL+C停止）
ping -c 4 8.8.8.8              # 指定发送4个包
```

---

### 4. 路由跟踪

```bash
traceroute www.google.com
```

如果系统未安装，可通过：

```bash
sudo apt install traceroute  # Debian/Ubuntu
sudo yum install traceroute  # CentOS/RHEL
```

---

### 5. 查看网络连接与端口

#### netstat (老牌)

```bash
netstat -tulnp
# -t: TCP
# -u: UDP
# -l: 监听端口
# -n: 数字显示
# -p: 显示进程ID
```

#### ss (现代替代)

```bash
ss -tuln
```

---

### 6. DNS 查询

```bash
nslookup www.google.com
dig www.google.com
```

---

### 7. 网络请求与下载工具

```bash
curl -I https://www.google.com    # 只请求响应头
curl https://www.google.com       # 请求页面内容

wget https://example.com/file.zip # 下载文件
```

---

### 8. 查看路由表

```bash
ip route show
```

---

### 9. 网络抓包（高级）

```bash
sudo tcpdump -i eth0 -c 10       # 抓取10个包
sudo tcpdump -i eth0 port 80     # 抓取80端口HTTP流量
```

---

## ✅ 实战练习

1. 使用 `ip addr` 查看你的网卡 IP 地址
2. 使用 `ping -c 3 www.baidu.com` 测试网络连通
3. 用 `ss -tuln` 查看本机监听端口
4. 用 `dig` 查询某个域名的DNS解析结果
5. 用 `curl -I` 查看某网站的响应头
