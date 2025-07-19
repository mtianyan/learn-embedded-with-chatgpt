太好了！`awk` 和 `sed` 是 Linux 中非常强大的文本处理工具，配合管道和重定向可完成自动化、日志分析、批量修改等任务。接下来我们系统学习它们的用法：

---

## 📦 第6部分：`awk` 和 `sed` 命令详解

---

## 🐦 awk：**按列处理神器**

### 💡 作用：

* 按\*\*列（字段）\*\*处理文本
* 自动按空格/Tab 分隔字段，可用 `$1`, `$2` 表示第一列、第二列
* 支持条件判断、计算、格式化输出

---

### 🔧 基本结构

```bash
awk 'pattern { action }' file
```

* `pattern`：匹配规则（可省略）
* `action`：对匹配的行执行的操作

---

### 🧪 常用例子

#### 1. 打印每行的第 1 列和第 3 列

```bash
awk '{ print $1, $3 }' file.txt
```

#### 2. 打印第 1 列等于 `apple` 的行

```bash
awk '$1 == "apple"' file.txt
```

#### 3. 统计行数

```bash
awk 'END { print NR }' file.txt
```

#### 4. 计算第 2 列数值总和

```bash
awk '{ sum += $2 } END { print sum }' file.txt
```

#### 5. 自定义字段分隔符（例如 CSV 文件）

```bash
awk -F ',' '{ print $1, $2 }' data.csv
```

---

## 🐍 sed：**按行处理与替换神器**

### 💡 作用：

* **按行匹配并修改文本**
* 替换、插入、删除、抽取内容

---

### 🔧 基本结构

```bash
sed 'command' file
```

可使用 `-i` 选项**就地修改文件**（慎用！）

---

### 🧪 常用例子

#### 1. 替换行中第一次出现的字符串

```bash
sed 's/apple/orange/' file.txt
```

#### 2. 替换所有出现的字符串（全局）

```bash
sed 's/apple/orange/g' file.txt
```

#### 3. 删除包含特定关键字的行

```bash
sed '/password/d' config.txt
```

#### 4. 插入内容到第3行前

```bash
sed '3i inserted line' file.txt
```

#### 5. 只打印第 2 到 4 行

```bash
sed -n '2,4p' file.txt
```

---

## 🚀 awk vs sed 对比

| 特性   | awk            | sed             |
| ---- | -------------- | --------------- |
| 处理单位 | 默认按**字段/列**处理  | 默认按**行**处理      |
| 典型用法 | 表格处理、条件筛选、数值计算 | 文本替换、插入、删除、批量改行 |
| 适用对象 | 表格化数据、日志字段等    | 配置文件、脚本文件、替换任务  |

---

## ✅ 实战练习

1. 用 `awk` 打印 `/etc/passwd` 的用户名（第1列）和默认 shell（最后一列）
2. 用 `awk` 筛选 `/etc/passwd` 中默认 shell 为 `/bin/bash` 的用户
3. 用 `sed` 将文本文件中所有 `foo` 替换为 `bar` 并保存到新文件
4. 删除某配置文件中所有包含 `debug` 的行
5. 只打印某日志文件的前 10 行的第 2 列（用管道 + awk）

---

非常好！我们通过 **真实场景案例** 来学习 `awk` 和 `sed`，这样你能真正理解这些命令的威力。

下面是几个**常用且实际工作的场景案例**，每一个都有输入示例、目标、命令和解释。

---

## 🎯 场景 1：从日志中提取错误行的时间和信息

### 📄 输入文件 `app.log`：

```
2025-07-19 10:00:01 [INFO] App started
2025-07-19 10:01:05 [ERROR] DB connection failed
2025-07-19 10:02:10 [INFO] User login
2025-07-19 10:03:15 [ERROR] File not found
```

### ✅ 目标：

提取所有 `[ERROR]` 行的时间戳和错误内容

### ✅ 命令（使用 awk）：

```bash
awk '/\[ERROR\]/ {print $1, $2, $3, $4}' app.log
```

### 📘 说明：

* `/\[ERROR\]/` 匹配包含 `[ERROR]` 的行
* `$1` 是日期，`$2` 是时间，`$3` 是 `[ERROR]`，`$4` 是错误内容

---

## 🎯 场景 2：替换 nginx 配置中的端口号

### 📄 输入文件 `nginx.conf`：

```
listen 80;
server_name localhost;
```

### ✅ 目标：

将 `listen 80;` 替换成 `listen 8080;`

### ✅ 命令（使用 sed）：

```bash
sed -i 's/listen 80;/listen 8080;/' nginx.conf
```

### 📘 说明：

* `-i` 表示**直接修改文件**
* `s/old/new/` 是 sed 的替换语法

---

## 🎯 场景 3：统计文本文件中出现次数最多的单词

### 📄 输入文件 `words.txt`：

```
apple banana apple orange apple banana
```

### ✅ 目标：

找出出现最多的单词及其次数

### ✅ 命令（awk + sort + uniq）：

```bash
tr ' ' '\n' < words.txt | sort | uniq -c | sort -nr | head -1
```

### 📘 说明：

* `tr ' ' '\n'`：将空格换行，变成一行一个词
* `uniq -c`：统计每个单词出现次数
* `sort -nr`：按数字倒序排序
* `head -1`：取出出现次数最多的一项

---

## 🎯 场景 4：提取 `/etc/passwd` 中用户名与默认 shell

### 📄 `/etc/passwd` 部分内容：

```
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
user1:x:1000:1000:User:/home/user1:/bin/bash
```

### ✅ 目标：

提取用户名（第1列）和 shell（第7列）

### ✅ 命令：

```bash
awk -F ':' '{ print $1, $7 }' /etc/passwd
```

---

## 🎯 场景 5：删除 HTML 中所有 `<script>` 标签内容（含多行）

### 📄 输入文件 `index.html`：

```html
<html>
<head>
<script>
console.log("Hacked!");
</script>
</head>
</html>
```

### ✅ 目标：

删除 `<script>...</script>` 整段内容

### ✅ 命令（使用 sed）：

```bash
sed '/<script>/,/<\/script>/d' index.html
```

### 📘 说明：

* `/pattern1/,/pattern2/` 表示范围匹配
* `d` 删除该范围内的所有行

---

你可以告诉我你平时有什么处理数据、日志、配置文件的需求，我可以继续帮你“定制场景”！

是否还要我补充一份：

* 🔖 `awk/sed 快速备忘清单`
* 📘 Markdown 整理好的 `awk/sed 教程 + 场景集`

还是继续学习 `xargs`、`cut`、`sort`、`uniq` 等组合技？


