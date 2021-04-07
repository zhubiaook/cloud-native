#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#define BUFSIZE 1024 * 1024

int main() {
    char buf[BUFSIZE];
    struct stat file_stat;

    int fd = open("/tmp/a.txt", O_RDONLY);
    fstat(fd, &file_stat);
    printf("File sieze is: %d\n", file_stat.st_size);

    char *map = mmap(NULL, file_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);

    int loop_count;
    loop_count = file_stat.st_size / (BUFSIZE);
    // 缺页异常时才真正分配物理内存
    int i = 0;
    for(; i < loop_count-1; i++) {
        memcpy(buf, map, BUFSIZE);
        map = map + BUFSIZE;
        printf("%d\n", i);
    }
    printf("read end\n");
    sleep(1000);
    return 0;
}
