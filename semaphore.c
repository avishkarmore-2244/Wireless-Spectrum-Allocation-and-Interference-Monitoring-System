#include <sys/sem.h>
#include "semaphore.h"

void lock(int semid) {
    struct sembuf s = {0, -1, 0};
    semop(semid, &s, 1);
}

void unlock(int semid) {
    struct sembuf s = {0, 1, 0};
    semop(semid, &s, 1);
}
