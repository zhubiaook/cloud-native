#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#define BUFSIZE 1024 * 1024

void block_read(FILE *stream) {
    char buf[BUFSIZE];
    int nr = 1;

    int i = 0;
    for(;; i++) {
        int ret = fread(buf, BUFSIZE, nr, stream);    
        if(ret < nr) {
            if(feof(stream)) {
                break;
            }
            if(ferror(stream)) {
                printf("error: fread\n");
                exit(1);
            }
        }
        printf("%5d %d\n", i, ret * BUFSIZE);
    }

    printf("fread end\n");
}


int main(int argc, char* argv[]) {
    char tmp_file[] = "/tmp/a.txt";

    FILE *stream = fopen(tmp_file, "r");
    if(stream == NULL) {
        printf("no file %s\n", tmp_file);
    }

    block_read(stream);
    fclose(stream);
    sleep(500);
}

