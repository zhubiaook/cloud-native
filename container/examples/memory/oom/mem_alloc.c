#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BLOCK_SIZE 1024 * 1024

int main(int argc, char* argv[]) {
    char *p;

    int i = 0;
    int num = atoi(argv[1]);

    // 循环申请内存，每次BLOCK_SIZE大小
    for(; i< num; i++) {
        p = malloc(BLOCK_SIZE);

        // 使用内存，引起缺页异常而分配物理内存
        memset(p, 0x00, BLOCK_SIZE);
        printf("p = %p\n", p);
    }
    free(p);
    printf("read end\n");
    sleep(1000);
}
