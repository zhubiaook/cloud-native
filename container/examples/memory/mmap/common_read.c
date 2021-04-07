/* common_read.c */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#define BUFSIZE 1024 * 1024

int main() {
    int fd;
    ssize_t num;
    char buf[BUFSIZE];
    struct stat file_stat;

    fd = open("/tmp/a.txt", O_RDWR);

    while(1) {
        num = read(fd, buf, BUFSIZE);
        // 读到文件末尾退出
        if(!num) {
            break;
        }
        printf("%d\n", num);
    }

    printf("read end\n");
    sleep(1000);
}
