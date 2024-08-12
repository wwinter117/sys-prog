#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void ls_dir(const char *path) {
    DIR *d;
    struct dirent *dir;
    if ((d = opendir(path)) == NULL) {
        perror("can not open dir");
        exit(EXIT_FAILURE);
    }
    while ((dir = readdir(d))) {
        printf("%s\n", dir->d_name);
    }
}

void ls_file(const char *path) {

}

int main(int argc, char *argv[]) {
    char *filename, *s;
    filename = "./";
    char buf[256];
    char path[256] = {0};

    if (argc > 1) {
        filename = argv[1];
    }
    struct stat st;

    if ((lstat(filename, &st)) < 0) {
        perror("no such file");
        exit(EXIT_FAILURE);
    }

    if (*path != '/') {
        if ((s = getcwd(buf, sizeof(buf))) == NULL) {
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
        strcpy(path, s);
        strcat(path, "/");
    }
    strcat(path, filename);

    if (S_ISDIR(st.st_mode)) {
        ls_dir(path);
    } else {
        ls_file(path);
    }
    return 1;
}