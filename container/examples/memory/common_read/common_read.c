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
    // fstat(fd, &file_stat);

    while(1) {
        num = read(fd, buf, BUFSIZE);
        if(!num) {
            break;
        }
        printf("%d\n", num);
        // sleep(1);
    }

    printf("read end\n");
    sleep(1000);
}
