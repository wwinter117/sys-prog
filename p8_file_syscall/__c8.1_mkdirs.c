#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define NEW_DIR_MODE 0766

/*
 * Syscall Usage of: mkdir, chdir, getcwd
 */
void mkdirs(char *path) {
    int r;
    char buf[256], *s;

    if ((r = mkdir(path, NEW_DIR_MODE)) < 0) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    r = chdir(path);
    if (r < 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    s = getcwd(buf, sizeof(buf));
    if (s == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    printf("CWD = %s\n", s);

    r = chdir("..");
    if (r < 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: mkdirs [path] ...\n");
        exit(EXIT_FAILURE);
    }
    char *path;
    while ((path = *++argv)) {
        mkdirs(path);
    }
    return 0;
}
