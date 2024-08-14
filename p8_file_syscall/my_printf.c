#include <stdio.h>

#define CTABLE "0123456789ABCDEF"
#define BASE 10

void printu(unsigned int x) {
    char c;
    if (x) {
        c = CTABLE[x % BASE];
        printu(x / BASE);
        putchar(c);
    }
}

int main() {
    printu(1234);
}