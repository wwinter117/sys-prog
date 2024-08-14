#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <ext2fs/ext2_fs.h>

void print(const char *str, unsigned int x) {
    printf("%-30s = %8d\n", str, x);
}

void ls_superblock(const char *dev) {
    int fd;
    int blksize;
    char buf[1024];
    struct ext2_super_block *p;

    // 打开设备文件
    if ((fd = open(dev, O_RDONLY)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (lseek(fd, 1024, SEEK_SET) < 0) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if ((read(fd, buf, 1024)) != 1024) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    p = (struct ext2_super_block *) buf;

    printf("%-30s = %8x ", "s_magic", p->s_magic);
    if (p->s_magic != 0xEF53) {
        printf("\nNot an EXT2 filesystem\n");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("EXT2 FS OK\n");

    // 打印超级块中的各种信息
    print("s_inodes_count", p->s_inodes_count);
    print("s_blocks_count", p->s_blocks_count);
    print("s_r_blocks_count", p->s_r_blocks_count);
    print("s_free_inodes_count", p->s_free_inodes_count);
    print("s_free_blocks_count", p->s_free_blocks_count);
    print("s_first_data_block", p->s_first_data_block);
    print("s_log_block_size", p->s_log_block_size);
    print("s_blocks_per_group", p->s_blocks_per_group);
    print("s_inodes_per_group", p->s_inodes_per_group);
    print("s_max_mnt_count", p->s_mnt_count);

    // 打印挂载时间和写入时间
    printf("s_mtime = %s", ctime((time_t * ) & p->s_mtime));
    printf("s_wtime = %s", ctime((time_t * ) & p->s_wtime));

    // 计算并打印块大小和 inode 大小
    blksize = 1024 << p->s_log_block_size;  // 计算块大小
    printf("block size = %d\n", blksize);
    printf("inode size = %d\n", p->s_inode_size);

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: superblock [dev]\n");
        return 0;
    }

    ls_superblock(argv[1]);
    return 1;
}
