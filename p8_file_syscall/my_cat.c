#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int fd, n;
    char buf[1024];

    fd = 0;
    if (argc > 1) {
        if ((fd = open(argv[1], O_RDONLY)) < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        if (write(1, buf, n)) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (n < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    if (fd != 0) {
        close(fd);
    }

    return 0;
}
