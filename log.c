#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

void write_log(int ch[], int dev[]) {

    int file = open("log.txt", O_CREAT | O_WRONLY, 0666);

    write(file, "Spectrum Result\n", 16);

    for (int i = 0; i < 10; i++) {
        if (ch[i] != -1) {
            char line[100];
            sprintf(line, "Channel %d -> Device %d\n", ch[i], dev[i]);
            write(file, line, strlen(line));
        }
    }

    close(file);
}
