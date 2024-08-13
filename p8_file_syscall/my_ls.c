#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>

void ls_dir(const char *path) {
    DIR *d;
    struct dirent *dir;

    if ((d = opendir(path)) == NULL) {
        perror("cannot open directory");
        exit(EXIT_FAILURE);
    }

    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            printf("%s\n", dir->d_name);
        }
    }

    closedir(d);
}

void ls_file(const char *path) {
    printf("%s\n", path);
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
