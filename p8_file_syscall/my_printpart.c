#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

struct partition {
    uint8_t drive;
    uint8_t head;
    uint8_t sector;
    uint8_t cylinder;
    uint8_t sys_type;
    uint8_t end_head;
    uint8_t end_sector;
    uint8_t end_sylinder;
    uint32_t start_sector;
    uint32_t nr_sectors;
};

void print_part(struct partition *p, int index, uint32_t base_start_sector) {
    uint32_t start = p->start_sector + base_start_sector;
    uint32_t end = start + p->nr_sectors - 1;
    printf("%2d  %10u  %10u  %10u  0x%02X\n", index, start, end, p->nr_sectors, p->sys_type);
}

void process_partition_table(int fd, uint32_t base_start_sector, int is_extended, int *partition_index) {
    char buf[512];
    struct partition *p;

    // 读取扇区数据
    lseek(fd, base_start_sector * 512, SEEK_SET);
    read(fd, buf, 512);
    p = (struct partition *)&buf[0x1BE];

    for (int i = 0; i < 4; i++) {
        if (p[i].sys_type != 0) {
            print_part(&p[i], (*partition_index)++, base_start_sector);
            // 如果是扩展分区，递归解析逻辑分区
            if (p[i].sys_type == 0x05 || p[i].sys_type == 0x0F) {
                process_partition_table(fd, p[i].start_sector + base_start_sector, 1, partition_index);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: myfdisk [fn]\n");
        return 0;
    }

    int fd;
    char *fname = argv[1];

    if ((fd = open(fname, O_RDONLY)) == -1) {
        fprintf(stderr, "Failed to open: %s\n", fname);
        return 0;
    }

    printf("Partition table of %s:\n", fname);
    printf(" Id   Start Sector    End Sector    # of Sectors  Type\n");

    int partition_index = 1;
    process_partition_table(fd, 0, 0, &partition_index);

    close(fd);
    return 1;
}
