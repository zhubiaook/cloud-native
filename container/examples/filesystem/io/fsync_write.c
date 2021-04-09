#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUFSIZE 1024 * 1024

static char mybuf[BUFSIZE];

void block_read(int fd) {
    read(fd, mybuf, BUFSIZE);    
}

void block_write(int src_fd, int dst_fd, int count) {
    block_read(src_fd);

    int i = 0;
    for(; i < count; i++) {
        int num = write(dst_fd, mybuf, BUFSIZE);
        printf("%5d %d\n", i, num);
    }
    fsync(dst_fd);
    printf("write end\n");
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: %s COUNT\n", argv[0]);
        exit(1);
    }

    int src_fd = open("/dev/zero", O_RDONLY);
    int dst_fd = open("/tmp/b.txt", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
    int count = atoi(argv[1]);

    block_write(src_fd, dst_fd, count);
    close(src_fd);
    close(dst_fd);
    sleep(500);
}

