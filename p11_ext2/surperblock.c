#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
//#include <ext2fs/ext2_fs.h>

typedef unsigned char __u8;
typedef unsigned short __u16;
typedef unsigned int __u32;
typedef unsigned long __u64;

struct ext2_super_block {
    __u32 s_inodes_count;         /* Inodes count */
    __u32 s_blocks_count;         /* Blocks count */
    __u32 s_r_blocks_count;       /* Reserved blocks count */
    __u32 s_free_blocks_count;    /* Free blocks count */
    __u32 s_free_inodes_count;    /* Free inodes count */
    __u32 s_first_data_block;     /* First Data Block */
    __u32 s_log_block_size;       /* Block size */
    __u32 s_log_frag_size;        /* Fragment size */
    __u32 s_blocks_per_group;     /* # Blocks per group */
    __u32 s_frags_per_group;      /* # Fragments per group */
    __u32 s_inodes_per_group;     /* # Inodes per group */
    __u32 s_mtime;                /* Mount time */
    __u32 s_wtime;                /* Write time */
    __u16 s_mnt_count;            /* Mount count */
    __u16 s_max_mnt_count;        /* Maximal mount count */
    __u16 s_magic;                /* Magic signature */
    __u16 s_state;                /* File system state */
    __u16 s_errors;               /* Behaviour when detecting errors */
    __u16 s_minor_rev_level;      /* minor revision level */
    __u32 s_lastcheck;            /* time of last check */
    __u32 s_checkinterval;        /* max. time between checks */
    __u32 s_creator_os;           /* OS */
    __u32 s_rev_level;            /* Revision level */
    __u16 s_def_resuid;           /* Default uid for reserved blocks */
    __u16 s_def_resgid;           /* Default gid for reserved blocks */

    /*
     * These fields are for EXT2_DYNAMIC_REV superblocks only.
     * Note: the difference between the compatible feature set and
     * the incompatible feature set is that if there is a bit set
     * in the incompatible feature set that the kernel doesn't
     * know about, it should refuse to mount the filesystem.
     *
     * e2fsck's requirements are more strict; if it doesn't know
     * about a feature in either the compatible or incompatible
     * feature set, it must abort and not try to meddle with
     * things it doesn't understand...
     */
    __u32 s_first_ino;            /* First non-reserved inode */
    __u16 s_inode_size;           /* size of inode structure */
    __u16 s_block_group_nr;       /* block group # of this superblock */
    __u32 s_feature_compat;       /* compatible feature set */
    __u32 s_feature_incompat;     /* incompatible feature set */
    __u32 s_feature_ro_compat;    /* readonly-compatible feature set */
    __u8 s_uuid[16];             /* 128-bit uuid for volume */
    char s_volume_name[16];      /* volume name */
    char s_last_mounted[64];     /* directory where last mounted */
    __u32 s_algorithm_usage_bitmap; /* For compression */

    /*
     * Performance hints.  Directory preallocation should only
     * happen if the EXT2_FEATURE_COMPAT_DIR_PREALLOC flag is on.
     */
    __u8 s_prealloc_blocks;      /* Nr of blocks to try to preallocate*/
    __u8 s_prealloc_dir_blocks;  /* Nr to preallocate for dirs */
    __u16 s_padding1;

    /*
     * Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.
     */
    __u8 s_journal_uuid[16];     /* uuid of journal superblock */
    __u32 s_journal_inum;         /* inode number of journal file */
    __u32 s_journal_dev;          /* device number of journal file */
    __u32 s_last_orphan;          /* start of list of inodes to delete */
    __u32 s_hash_seed[4];         /* HTREE hash seed */
    __u8 s_def_hash_version;     /* Default hash version to use */
    __u8 s_jnl_backup_type;
    __u16 s_desc_size;            /* size of group descriptor */
    __u32 s_default_mount_opts;
    __u32 s_first_meta_bg;        /* First metablock block group */
    __u32 s_mkfs_time;            /* When the filesystem was created */
    __u32 s_jnl_blocks[17];       /* Backup of the journal inode */

    __u32 s_blocks_count_hi;      /* Blocks count high 32 bits */
    __u32 s_r_blocks_count_hi;    /* Reserved blocks count high 32 bits */
    __u32 s_free_blocks_hi;       /* Free blocks count high 32 bits */
    __u16 s_min_extra_isize;      /* All inodes have at least # bytes */
    __u16 s_want_extra_isize;     /* New inodes should reserve # bytes */
    __u32 s_flags;                /* Miscellaneous flags */
    __u16 s_raid_stride;          /* RAID stride */
    __u16 s_mmp_interval;         /* # seconds to wait in MMP checking */
    __u64 s_mmp_block;            /* Block for multi-mount protection */
    __u32 s_raid_stripe_width;    /* blocks on all data disks (N * stride)*/
    __u8 s_log_groups_per_flex;  /* FLEX_BG group size */
    __u8 s_reserved_char_pad;
    __u16 s_reserved_pad;
    __u32 s_reserved[162];        /* Padding to the end of the block */
};

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
