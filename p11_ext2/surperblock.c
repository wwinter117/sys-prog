#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ext2fs/ext2_fs.h>

void ls_superblock(const char *dev) {
    int fd;
    char buf[1024];
    struct ext2_super_block *p;
    if ((fd = open(dev, O_RDONLY)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    lseek(fd, 1024, SEEK_SET);
    if ((read(fd, buf, 1024)) != 1024) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 16; i++) {
        printf("%02x ", buf[i]);
    }
    printf("\n");

    p = (struct ext2_super_block *) buf;

    printf("%-30s = %8x\n", "s_magic", p->s_magic);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: superblock [dev]\n");
        return 0;
    }
    ls_superblock(argv[1]);
    return 1;
}