# 文件IO

## 文件操作
## 系统调用

### 常用
```text
mkdir
chdir
chmod
getcwd

stat
fstat
lstat

open
close
read
write
lseek
```
### 链接文件

**硬链接**
```shell
ln oldpath newpath
```

**软链接（符号链接）**
```shell
ln -s oldpath newpath
```

### stat系统调用

原理：查找文件的索引节点，并将信息从索引节点复制到stat结构体中

### 目录文件

```text
opendir
readdir
```

### 
## I/O库函数