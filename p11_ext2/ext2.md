# EXT2文件系统

## 创建一个ext2虚拟磁盘

```shell
$ dd if=/dev/zero of=vdisk bs=1024 count=1440
$ mke2fs vdisk
```