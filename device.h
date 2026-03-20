#ifndef DEVICE_H
#define DEVICE_H

struct Req {
    int id;
    int bw;
    int signal;
};

struct Req create_request(int id, int round);

// thread functions
void* transmit(void* arg);
void* signal_check(void* arg);

#endif
