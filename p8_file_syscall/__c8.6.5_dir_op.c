//
// Created by wwinter on 2024/8/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: lsdir [path]\n");
        exit(EXIT_FAILURE);
    }
    DIR *dir;
    if ((dir = opendir(argv[1])) == NULL) {
        perror("open dir");
        exit(EXIT_FAILURE);
    }
    struct dirent *d;
    while ((d = readdir(dir))) {
        printf("%s\n", d->d_name);
    }
    return 1;
}