#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int fd, n;
    char buf[1028];

    fd = 0;
    if (argc > 1) {
        if ((fd = open(argv[1], O_RDONLY)) < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }

    while ((n = read(fd, buf, sizeof(buf)))) {
        write(1, buf, n);
    }
}
