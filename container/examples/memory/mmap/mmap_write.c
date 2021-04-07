#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int main() {
    // mmapped array of char
    char *text = "hello world";

    printf("will write text: %s\n", text);

    // open file description
    int fd = open("./c.txt", O_RDWR | O_CREAT);

    if(fd == -1) {
        perror("open mmapped");
        exit(1);
    }

    // streth the file size to the size of the mmapped array of char
    int textsize = strlen(text);


    /*
     *  下面两步是为了扩展文件的长度与要映射的内存空间一样
     */
    // 将文件指针从文件头向后移动textsize个位置
    if(lseek(fd, textsize, SEEK_SET) == -1) {
        close(fd);
        perror("lseek");
        exit(1);
    }

    // 文件末尾写入空字符: 0x0，文件结束标志
    if(write(fd, "", 1) == -1) {
        close(fd);
        perror("write");
        exit(1);
    }

    // 将文件映射到内存
    char *map = mmap(NULL, textsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("map");
        exit(1);
    }

    // 关闭文件描述符, 后面是磁盘与内存的映射，与文件描述符无关
    close(fd);

    // 向内存空间写入字符串，自动映射到文件
    size_t i;
    for(i=0; i < textsize; i++) {
        map[i] = text[i];
    }

    // 将内存中的数据刷到磁盘
    if(msync(map, textsize, MS_SYNC) == -1) {
        perror("msync");
    }

    // 关闭映射
    if(munmap(map, textsize) == -1) {
        close(fd);
        perror("mumap");
        exit(1);
    }
    return 0;
}
