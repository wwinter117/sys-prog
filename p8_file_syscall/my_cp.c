#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: mycp [src] [dst]\n");
        exit(EXIT_FAILURE);
    }
    int fd1, fd2, n;
    char buf[1024];
    if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if ((fd2 = open(argv[2], O_WRONLY | O_CREAT, 0766)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while ((n = read(fd1, buf, sizeof(buf))) > 0) {
        write(fd2, buf, n);
    }

    close(fd1);
    close(fd2);
    return 0;
}