#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

#define t1 "xwrxwrxwr"

void ls_file(const char *path) {
    struct stat s;
    if (lstat(path, &s) < 0) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }

    // 0100 000 111 101 101
    for (int i = 15; i >= 0; i--) {
        printf("%d", (s.st_mode >> i) & 1);
    }

    if (S_ISDIR(s.st_mode)) {
        printf("d");
    } else if (S_ISREG(s.st_mode)) {
        printf("-");
    } else {
        printf("l");
    }

    for (int i = 8; i >= 0; --i) {
        if (s.st_mode & (1 << i)) {
            printf("%c", t1[i]);
        } else {
            printf("-");
        }
    }

    printf("%4d", s.st_nlink);
    printf("%4d", s.st_gid);
    printf("%4d", s.st_uid);
    printf("%8lld", s.st_size);

    printf("%s\n", path);
}

void ls_dir(const char *path) {
    DIR *d;
    struct dirent *dir;

    if ((d = opendir(path)) == NULL) {
        perror("cannot open directory");
        exit(EXIT_FAILURE);
    }

    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            ls_file(dir->d_name);
//            printf("%s\n", dir->d_name);
        }
    }

    closedir(d);
}

char *realpath1(const char *filename, char *path) {
    char *s;
    char buf[PATH_MAX];
    if (*filename != '/') {
        if ((s = getcwd(buf, 256)) == NULL) {
            perror("getcwd");
            return NULL;
        }
        strcpy(path, s);
        strcat(path, "/");
    }
    strcat(path, filename);
    return path;
}

int main(int argc, char *argv[]) {
    char path[PATH_MAX];
    struct stat st;
    const char *filename = argc > 1 ? argv[1] : "./";

    if (lstat(filename, &st) < 0) {
        perror("no such file");
        exit(EXIT_FAILURE);
    }

    if (realpath1(filename, path) == NULL) {
        perror("realpath failed");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(st.st_mode)) {
        ls_dir(path);
    } else {
        ls_file(path);
    }

    return 0;
}
