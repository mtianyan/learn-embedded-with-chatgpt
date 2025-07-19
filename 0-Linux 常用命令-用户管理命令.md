很好！我们现在进入 Linux 的 **用户管理命令**，这是系统管理中非常重要的一环。掌握这部分内容后，你将能：

* 创建、删除用户与用户组
* 设置或修改密码
* 修改用户权限和登录信息
* 管理用户组归属
* 限制或锁定账户

---

## 🧑‍💻 第 2 部分：用户与用户组管理

### 📌 用户管理命令总览

| 命令                      | 功能                  |
| ----------------------- | ------------------- |
| `whoami` / `id`         | 查看当前用户 / UID/GID 信息 |
| `adduser` / `useradd`   | 添加新用户               |
| `passwd`                | 设置或修改用户密码           |
| `usermod`               | 修改用户信息              |
| `deluser` / `userdel`   | 删除用户                |
| `groupadd` / `groupdel` | 添加 / 删除用户组          |
| `gpasswd` / `groupmod`  | 设置用户组密码 / 修改组       |
| `groups`                | 查看用户所属组             |
| `su` / `sudo`           | 以其他用户身份执行命令（切换用户）   |

---

### 👥 1. 查看当前用户信息

```bash
whoami         # 当前用户名
id             # 查看 UID/GID 和所属组
groups         # 查看你属于哪些组
```

---

### ➕ 2. 添加用户与组

#### 添加用户（推荐用 `adduser`）

```bash
sudo adduser newuser      # 会创建 home 目录并提示设置密码
```

#### 添加用户组

```bash
sudo groupadd devteam
```

#### 添加用户到组

```bash
sudo usermod -aG devteam newuser  # -a 表示追加，-G 表示加入组
sudo usermod -aG sudo,docker,devteam newuser
```

🔍 验证：

```bash
groups newuser
```

---

### 🔑 3. 设置或修改密码

```bash
sudo passwd newuser
# 输入新密码两次即可
```

---

### 📝 4. 修改用户信息

```bash
sudo usermod -c "开发人员" newuser       # 添加注释
sudo usermod -s /bin/bash newuser       # 修改默认 shell
sudo usermod -d /home/myuser newuser    # 修改 home 目录
```

---

### 🗑️ 5. 删除用户或组

```bash
sudo deluser newuser
sudo deluser --remove-home newuser    # 顺带删 home 目录

sudo groupdel devteam
```

---

### 🧙 6. 提权 & 临时切换用户

```bash
su - root                 # 切换到 root 账户
sudo command              # 以管理员权限执行命令
sudo -u otheruser cmd     # 以其他用户身份执行命令
```

---

## ✅ 实战练习任务（可在本地虚拟机环境中尝试）

1. 创建一个用户 `devuser`，并设置密码为 `123456`
2. 创建用户组 `projectX`，将 `devuser` 加入该组
3. 修改 `devuser` 的默认 shell 为 `/bin/bash`
4. 删除 `devuser` 并清除其 home 目录
5. 验证你当前用户是否在 `sudo` 用户组内

---

你可以先练习这些命令，或者告诉我你要一份 Markdown 笔记/总结用于 GitHub。我也可以在接下来继续讲解下一章节：

> 🔌 第 3 部分：网络管理命令（如 `ip`, `ping`, `netstat`, `ss`, `curl` 等）

是否继续？或者需要补充哪一块？


非常实用的操作！下面是**给用户添加 sudo 权限** 和 **移除 sudo 权限** 的完整方法。

---

## ✅ 一、给用户添加 sudo 权限

### 方法 1：添加到 `sudo` 组（推荐方式）

适用于大多数基于 Debian/Ubuntu 的系统：

```bash
sudo usermod -aG sudo 用户名
```

例如：

```bash
sudo usermod -aG sudo newuser
```

这会把 `newuser` 加入 `sudo` 组，而 `/etc/sudoers` 通常允许该组使用 sudo。

**修改后要重新登录或用 `su - 用户名` 才能生效！**

---

### 方法 2：单独授予 sudo 权限（不加入 sudo 组）

编辑一个 `sudoers` 配置文件：

```bash
echo "newuser ALL=(ALL) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/newuser
chmod 0440 /etc/sudoers.d/newuser
```

这将允许 `newuser` 无密码执行任何 sudo 命令。

---

## ❌ 二、移除用户 sudo 权限

### 方法 1：从 `sudo` 组中移除（推荐）

```bash
sudo gpasswd -d 用户名 sudo
```

例如：

```bash
sudo gpasswd -d newuser sudo
```

这会把 `newuser` 从 `sudo` 组移除。重新登录后生效。

---

### 方法 2：删除 `/etc/sudoers.d/用户名` 文件（如果你用的是方法 2 授权的）

```bash
sudo rm /etc/sudoers.d/newuser
```

---

## 🧪 验证是否拥有 sudo 权限

切换到目标用户后：

```bash
whoami         # 查看当前是谁
sudo whoami    # 测试是否能以 sudo 执行
```

* 如果输出 `root`，说明 sudo 正常
* 如果提示“not in the sudoers file”，说明没有 sudo 权限

---

## 🧠 小结

| 操作           | 命令                                            |
| ------------ | --------------------------------------------- |
| 添加 sudo 权限   | `usermod -aG sudo 用户名`                        |
| 添加 sudo（不进组） | `echo "用户 ALL=(ALL) ALL" > /etc/sudoers.d/用户` |
| 移除 sudo（从组）  | `gpasswd -d 用户名 sudo`                         |
| 移除 sudo（删规则） | `rm /etc/sudoers.d/用户名`                       |

---

需要我写一个 Bash 脚本，一键给用户添加或撤销 sudo 权限吗？

这是个好问题！我们来解释清楚：

---

## ✅ `usermod -aG` 与 `gpasswd -a` 的区别

| 操作目的       | 推荐命令               | 说明             |
| ---------- | ------------------ | -------------- |
| **添加用户到组** | `usermod -aG 组 用户` | 通常用于“设置用户的附加组” |
| **添加用户到组** | `gpasswd -a 用户 组`  | 通常用于“向某组添加成员”  |

---

## 🔍 区别详解

### 1. `usermod -aG` 是**从用户角度**设置

* 修改用户的 **附加组** 列表（`/etc/group` 和 `/etc/passwd`）
* 常用于创建用户或批量设定组
* 示例：

  ```bash
  sudo usermod -aG sudo newuser
  ```

### 2. `gpasswd -a` 是**从组角度**设置

* 把用户添加到 **某个组的成员列表**
* 本质上修改 `/etc/group` 文件中该组的成员字段
* 示例：

  ```bash
  sudo gpasswd -a newuser sudo
  ```

---

## ✅ 推荐使用场景对比

| 场景                      | 推荐命令                 |
| ----------------------- | -------------------- |
| 添加用户到多个组                | `usermod -aG`        |
| 添加用户到某个组（单个）            | `gpasswd -a`         |
| 从组中移除用户                 | `gpasswd -d` ✅唯一安全方式 |
| 批量修改用户信息（比如 shell、home） | `usermod`            |

---

## 🧠 小结

* 添加：`usermod -aG sudo newuser` ✅ 安全（注意必须加 `-a`）
* 添加：`gpasswd -a newuser sudo` ✅ 同样可行
* 移除：必须用 `gpasswd -d newuser sudo` ✅

**你选择哪个，其实都可以，只是 `usermod -aG` 在创建用户或批量管理时更直观，`gpasswd` 在精确管理组成员时更方便。**

---

需要我帮你写一个可以选择 `添加` / `移除` 用户到指定组的脚本吗？

