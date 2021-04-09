#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#define BUFSIZE 1024 * 1024

void nonblock_read(int fd) {
    char buf[BUFSIZE];

    int i = 0;
    for(;; i++) {
        int ret = read(fd, buf, BUFSIZE);    
        if(ret == 0) {
            break;
        } else if(ret == -1 && errno != EAGAIN) {
            error(1, errno, "read");
        }
        printf("%5d %d\n", i, ret);
    }

    printf("read end\n");
}


int main(int argc, char* argv[]) {
    char tmp_file[] = "/tmp/a.txt";

    int fd = open(tmp_file, O_RDONLY|O_NONBLOCK);
    if(fd == -1) {
        printf("no file %s\n", tmp_file);
    }

    nonblock_read(fd);
    close(fd);
    sleep(500);
}

