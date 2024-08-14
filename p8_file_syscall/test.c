#include <stdio.h>
#include <regex.h>

int main() {
    const char *pattern = ".*"; // 正则表达式模式
    const char *text = "Hello, world";      // 要匹配的字符串

    regex_t regex;
    int ret;

    // 编译正则表达式
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // 执行正则表达式匹配
    ret = regexec(&regex, text, 0, NULL, 0);
    if (!ret) {
        printf("Match found\n");
    } else if (ret == REG_NOMATCH) {
        printf("No match found\n");
    } else {
        char msgbuf[100];
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    // 释放正则表达式的内存
    regfree(&regex);

    return 0;
}
