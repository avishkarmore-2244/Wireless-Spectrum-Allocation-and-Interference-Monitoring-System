#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "device.h"

void* transmit(void* arg) {
    int id = *(int*)arg;
    // simple simulation
    // no heavy printing (clean output)
    return NULL;
}

void* signal_check(void* arg) {
    int id = *(int*)arg;
    return NULL;
}

struct Req create_request(int id, int round) {

    pthread_t t1, t2;

    // create threads
    pthread_create(&t1, NULL, transmit, &id);
    pthread_create(&t2, NULL, signal_check, &id);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    struct Req r;
    r.id = id;
    r.bw = id * 5 + round;
    r.signal = rand() % 100;

    return r;
}
