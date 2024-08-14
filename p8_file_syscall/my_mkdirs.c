#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define NEW_DIR_MODE 0766

/*
 * Syscall Usage of: mkdir, chdir, getcwd
 */
void mkdirs(char *path) {
    char buf[256], *s;
    struct stat stat;
    stat.st_mode

    if ((mkdir(path, NEW_DIR_MODE)) < 0) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    if ((chdir(path)) < 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    if ((s = getcwd(buf, sizeof(buf))) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    printf("mkdir: %s\n", s);

    if ((chdir("..")) < 0) {
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
