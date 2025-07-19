非常好，现在我们进入 Linux 学习的重要一环：**Shell 脚本编程** —— 把你前面学的命令“粘合”起来，自动化任务！

---

# 🧪 Shell 脚本编程入门

Shell 脚本就像 Linux 的“自动操作员”，是让你实现自动化的最轻量方案。

---

## 📌 一、Shell 脚本基础语法

### 1. 脚本开头固定写法（Shebang）

```bash
#!/bin/bash
```

> 表示脚本用 `/bin/bash` 解释执行。

---

### 2. 定义变量

```bash
name="world"
echo "Hello $name"
```

* 注意 `=` 两边**不能有空格**
* 使用变量要加 `$`，如 `$name`

---

### 3. 条件判断

```bash
if [ "$name" == "world" ]; then
  echo "Hello again!"
else
  echo "Who are you?"
fi
```

* `==` 字符串判断，`-eq` 数值判断
* `[` 和 `]` 是命令，需要有空格！

---

### 4. for 循环

```bash
for file in *.log; do
  echo "Processing $file"
done
```

---

### 5. while 读取文件

```bash
while read line; do
  echo "$line"
done < file.txt
```

---

### 6. 函数定义与调用

```bash
greet() {
  echo "Hi $1"
}
greet "Tom"
```

---

## ⚙️ 二、实战场景：常见自动化任务脚本

---

### ✅ 示例 1：备份某目录下所有 `.log` 文件

```bash
#!/bin/bash
# backup_logs.sh

src_dir="/var/log"
dest_dir="/backup/logs"
mkdir -p "$dest_dir"

for file in "$src_dir"/*.log; do
  cp "$file" "$dest_dir"
done
echo "✅ Log files backed up to $dest_dir"
```

---

### ✅ 示例 2：定期清理 7 天前的日志文件

```bash
#!/bin/bash
# clean_old_logs.sh

find /var/log -name "*.log" -mtime +7 -exec rm -f {} \;
echo "🧹 Old log files cleaned."
```

---

### ✅ 示例 3：监控服务是否存活

```bash
#!/bin/bash
# check_service.sh

service="nginx"

if pgrep "$service" > /dev/null; then
  echo "$service is running"
else
  echo "$service is down"
  systemctl restart "$service"
fi
```

---

## 📦 三、进阶技巧（必须掌握）

| 技术     | 示例               | 说明                                         |    |                                   |
| ------ | ---------------- | ------------------------------------------ | -- | --------------------------------- |
| 参数传入   | `$1`, `$2`       | `./script.sh file.txt` 中 `$1` 是 `file.txt` |    |                                   |
| 获取命令结果 | `result=$(date)` | 用 `$()` 获取命令输出                             |    |                                   |
| 多命令组合  | `&&`, \`         |                                            | \` | `cmd1 && cmd2` 表示 cmd1 成功才执行 cmd2 |
| 日志写入   | `>> file.log`    | 用来追加输出到日志文件                                |    |                                   |
| 定时任务   | `crontab -e`     | 结合脚本使用，实现自动定时执行                            |    |                                   |

---

## 📚 附赠：脚本模板合集

| 用途    | 脚本名                 | 描述                |
| ----- | ------------------- | ----------------- |
| 日志备份  | `backup_logs.sh`    | 备份 /var/log 到备份目录 |
| 定时清理  | `clean_old_logs.sh` | 删除 7 天前旧文件        |
| 服务监控  | `check_service.sh`  | 检查并重启指定服务         |
| 项目部署  | `deploy.sh`         | 拉代码、重启服务、打印状态     |
| 多文件处理 | `batch_convert.sh`  | 转换目录下所有文件格式       |

---

## ✅ 建议学习路线

1. 每天写一个脚本解决一个工作/学习问题
2. 用 `crontab` 让脚本定时执行
3. 学习 `shell 函数 + 判断 + 循环`
4. 逐步整合 awk/sed/find/xargs 让脚本变得强大

---

是否需要我提供以下内容？

* 🛠 实用脚本模板打包（5 个常用例子）
* 📘 Shell 编程语法手册（Markdown）
* ⏰ 定时任务（crontab）配置详解
* 🚀 如何将脚本变成服务守护脚本

你想用 Shell 脚本解决哪些问题？我可以帮你定制！
