#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "mysignal.h"

void handler(int sig) {
    if (sig == SIGINT) {
        printf("\nSystem Stopped\n");
        exit(0);
    }
}
