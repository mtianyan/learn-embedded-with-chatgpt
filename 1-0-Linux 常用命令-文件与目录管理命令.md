太好了！我们可以系统性地学习 Linux 命令。我会以模块方式分阶段带你掌握每一类命令，每一部分包含：

1. 常用命令列表
2. 每条命令的作用和常见参数
3. 使用示例（含说明）
4. ChatGPT 小提示：常见坑点或使用技巧

---

### 🗂️ 第 1 部分：文件与目录管理命令

#### 🚀 目标：你将能熟练完成以下操作：

* 浏览目录、查看文件内容
* 创建、删除、移动、重命名文件/文件夹
* 修改文件权限、所有权
* 查找文件

---

#### 📁 基础命令表

| 命令                               | 功能          |
| -------------------------------- | ----------- |
| `ls`                             | 列出目录内容      |
| `cd`                             | 切换目录        |
| `pwd`                            | 显示当前路径      |
| `mkdir` / `rmdir`                | 创建 / 删除目录   |
| `touch`                          | 创建空文件       |
| `cp`                             | 拷贝文件/目录     |
| `mv`                             | 移动/重命名文件或目录 |
| `rm`                             | 删除文件或目录     |
| `cat` / `less` / `head` / `tail` | 查看文件内容      |
| `chmod`                          | 修改权限        |
| `chown`                          | 修改所有者       |
| `find`                           | 查找文件        |
| `file`                           | 查看文件类型      |

---

### 👣 开始练习 1：文件浏览与操作

```bash
# 列出当前目录内容（包括隐藏文件）
ls -la

# 创建目录
mkdir test_dir

# 进入目录
cd test_dir

# 创建文件
touch hello.txt

# 写入内容（方式1：重定向）
echo "hello linux" > hello.txt

# 查看文件内容
cat hello.txt

# 拷贝文件
cp hello.txt copy.txt

# 重命名文件
mv copy.txt newname.txt

# 删除文件
rm newname.txt

# 删除目录
cd .. && rm -r test_dir
```

---

📌 **ChatGPT 小贴士**：

* `rm -r` 会递归删除目录，危险操作谨慎使用！
* `mv old new` 可以用于重命名或移动文件
* `chmod +x your_script.sh` 让脚本具备执行权限

---

好的，我们继续深入学习 Linux 中的文件权限、所有权修改，以及查找相关命令。这部分非常重要，掌握后你就能控制系统中文件的访问和安全性。

---

## 🔐 文件权限与所有权管理

Linux 中每个文件或目录都有 3 个角色的权限设置：

| 用户角色           | 说明           |
| -------------- | ------------ |
| **u** (user)   | 文件**所有者**    |
| **g** (group)  | 文件所属的**用户组** |
| **o** (others) | 其他人          |
| **a** (all)    | 所有用户（u+g+o）  |

权限分为 3 种：

| 权限   | 符号 | 含义                |
| ---- | -- | ----------------- |
| 读权限  | r  | 查看文件内容，列出目录内容     |
| 写权限  | w  | 修改文件内容，添加/删除目录内容  |
| 执行权限 | x  | 运行文件，将目录设为可进入（cd） |

你可以用以下命令查看权限：

```bash
ls -l
```

输出例子：

```bash
-rwxr-xr--  1 user group  1234 Jul 19 15:00 hello.sh
```

说明：

* `-rwxr-xr--` 表示权限（前三个是 user，中三个是 group，后三个是 other）
* `1 user group` 表示拥有者是 `user`，用户组是 `group`

---

这是一条典型的 Unix/Linux/macOS 中使用 `ls -l` 命令显示的文件/目录信息，例如：

```
drwxr-xr-x  26 mtianyan  staff  832  6 14 21:22 目录名
```

下面我们逐一解释每个字段的含义：

| 字段 | 示例值          | 说明                                                |
| -- | ------------ | ------------------------------------------------- |
| 1  | `drwxr-xr-x` | 文件类型 + 权限串：<br>`d` 表示目录，后面是权限（owner/group/others） |
| 2  | `26`         | 硬链接数，表示该目录下包含的子目录（包括 `.` 和 `..`）数量或文件的硬链接数        |
| 3  | `mtianyan`   | 拥有者用户名                                            |
| 4  | `staff`      | 所属用户组名                                            |
| 5  | `832`        | 文件/目录大小，单位为字节（目录大小通常是包含的元数据）                      |
| 6  | `6`          | 最后修改的月份（6月）                                       |
| 7  | `14`         | 最后修改的日期（14日）                                      |
| 8  | `21:22`      | 最后修改时间（21:22）                                     |
| 9  | `目录名`        | 文件或目录的名称                                          |

---

### 🔍 第一个字段权限详解：`drwxr-xr-x`

* 第1个字符：`d` 表示这是一个目录；如果是 `-` 则表示是普通文件，`l` 表示是链接文件等。
* 接下来的9个字符表示权限，按每3位分为一组：

| 位置  | 含义    | 示例    | 说明         |
| --- | ----- | ----- | ---------- |
| 1-3 | 拥有者权限 | `rwx` | 读、写、执行权限   |
| 4-6 | 所在组权限 | `r-x` | 读、执行（无写权限） |
| 7-9 | 其他人权限 | `r-x` | 读、执行       |

---

如需我帮你记住这个格式，或给出常用权限组合对照表、权限修改命令 (`chmod`) 示例，也可以继续告诉我。


### ✏️ 修改权限：`chmod`

#### 方式 1：**符号模式**

```bash
chmod u+x file      # 给用户添加执行权限
chmod g-w file      # 移除组的写权限
chmod o=r file      # 将其他用户权限设置为只读
chmod a+x script.sh # 所有用户添加执行权限
```

| 命令          | 含义                               | 举例效果                 |
| ----------- | -------------------------------- | -------------------- |
| `chmod +x`  | **给所有人添加可执行权限（x）**，**保留原来的读写权限** | 把 `644` 变成 `755`     |
| `chmod 777` | 给**所有人**添加**读、写、执行权限**（`rwx`）    | 不管原来权限是多少，全部变成 `rwx` |

#### 方式 2：**数字模式**

每种权限有一个数值：

| 权限 | 数值 |
| -- | -- |
| r  | 4  |
| w  | 2  |
| x  | 1  |

三位数字分别表示 **user / group / other** 的权限

```bash
chmod 755 script.sh   # user: rwx (7), group: r-x (5), other: r-x (5)
chmod 644 note.txt    # user: rw- (6), group: r-- (4), other: r-- (4)
```

---

### 👤 修改所有者：`chown`

```bash
chown user file          # 改为某个用户所有
chown user:group file    # 改为某用户及组所有
chown -R user:group dir/ # 递归修改整个目录
```

示例：

```bash
sudo chown root:root config.ini
```

---

## 🔍 文件查找命令

### 1️⃣ `find`：按路径递归查找

```bash
# 在当前目录查找名为 myfile.txt 的文件
find . -name "myfile.txt"

# 查找所有以 .log 结尾的文件
find /var/log -type f -name "*.log"

# 查找修改时间在最近一天内的文件
find . -mtime -1

# 查找大于 10MB 的文件
find . -type f -size +10M

# 删除空目录
find . -type d -empty -delete
```

### 2️⃣ `locate`：快速全盘查找（基于索引）

```bash
sudo updatedb         # 第一次使用需要更新数据库
locate config.json    # 快速找到文件路径
```

---

### ✅ 实战练习任务（建议动手尝试）

1. 创建 test 文件并设置：

   * 只有 owner 可以读写
   * group 和 other 不能访问
2. 编写一个 shell 脚本 `hello.sh`，修改权限为所有人可执行
3. 在某个目录下查找所有 `.sh` 脚本并显示出来
4. 将一个目录及其子文件的所有者改为 `nobody:nogroup`

需要答案或者我帮你检查练习代码也可以说。

好的！这里是刚才提到的 **4 个实战练习题** 的参考答案（命令行示例），你可以逐条尝试练习：

---

### ✅ 1. 创建 test 文件，并设置：

* **只有 owner 可以读写**
* **group 和 other 不能访问**

```bash
touch test
chmod 600 test        # 6 = rw- (user), 0 = --- (group), 0 = --- (other)
ls -l test
# 输出应类似：
# -rw------- 1 your_user your_group 0 Jul 19 17:00 test
```

---

### ✅ 2. 编写 shell 脚本 `hello.sh`，修改权限为所有人可执行

```bash
echo -e '#!/bin/bash\necho "Hello, Linux!"' > hello.sh
chmod +x hello.sh
ls -l hello.sh
# 输出应类似：
# -rwxr-xr-x 1 your_user your_group ... hello.sh

./hello.sh
# 输出：
# Hello, Linux!
```

---

### ✅ 3. 在某个目录下查找所有 `.sh` 脚本并显示出来

```bash
# 假设目录为 ~/scripts
find ~/scripts -type f -name "*.sh"

# 示例输出：
# /home/user/scripts/start.sh
# /home/user/scripts/install.sh
```

---

### ✅ 4. 将一个目录及其子文件的所有者改为 `nobody:nogroup`

⚠️ 注意：你需要 `sudo` 权限，`nobody:nogroup` 通常是系统中限制权限的用户/组。

```bash
sudo chown -R nobody:nogroup /path/to/your/dir

# 验证
ls -l /path/to/your/dir
```

---

如果你有任何输出不对，或者你用的是非 Debian 系（如 RedHat），`nogroup` 可能会叫做 `nobody`，可以用 `cat /etc/group | grep nobody` 看系统支持的用户组。

