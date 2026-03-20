#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <time.h>

#include "device.h"
#include "semaphore.h"
#include "log.h"
#include "mysignal.h"

#define DEVICES 3
#define ROUNDS 2

struct Data {
    int channel[10];
    int device[10];
};

int main() {
	int print_sem = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
	semctl(print_sem, 0, SETVAL, 1);
	
    	srand(time(NULL));

    	signal(SIGINT, handler);

    	int fd[2];
    	pipe(fd);

    	int shmid = shmget(IPC_PRIVATE, sizeof(struct Data), 0666 | IPC_CREAT);
    	struct Data *sh = (struct Data*) shmat(shmid, NULL, 0);

    	for (int i = 0; i < 10; i++) {
        			sh->channel[i] = -1;
        			sh->device[i] = -1;
    }

    	int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    	semctl(semid, 0, SETVAL, 1);

    	printf("Spectrum Manager Started\n");

    	for (int i = 0; i < DEVICES; i++) {

        	if (fork() == 0) {

            		close(fd[0]);

        for (int r = 0; r < ROUNDS; r++) {

                struct Req req = create_request(i+1, r);

		char msg[100];

		sprintf(msg, "Device %d requesting → BW=%d MHz, Signal=%d dBm\n", req.id, req.bw, req.signal);

		lock(print_sem);
		write(1, msg, strlen(msg));
		unlock(print_sem);

		fflush(stdout);   // 🔥 important

		write(fd[1], &req, sizeof(req));
            }

            close(fd[1]);
            exit(0);
        }
    }

    close(fd[1]);
    
	sleep(1);
   printf("\n--- Manager Receiving Requests ---\n");

    for (int i = 0; i < DEVICES * ROUNDS; i++) {
    	

        struct Req req;
        read(fd[0], &req, sizeof(req));
        
        sleep(2);
        
	char msg[100];

	sprintf(msg, "\nDevice %d → BW=%d MHz, Signal=%d dBm\n", req.id, req.bw, req.signal);

	lock(print_sem);
	write(1, msg, strlen(msg));
	unlock(print_sem);

        int ch = req.id % 2;
        int final_ch = -1;

        lock(semid);

        if (sh->channel[ch] == -1) {

            sh->channel[ch] = ch;
            sh->device[ch] = req.id;

            final_ch = ch;

          char msg[100];

	sprintf(msg, "Manager: Channel %d given\n", final_ch);

	lock(print_sem);
	write(1, msg, strlen(msg));
	unlock(print_sem);
	
        }
       else {
    		char msg[150];

		sprintf(msg, "Manager: Interference on Channel %d between Device %d and Device %d\n", ch, sh->device[ch], req.id);

		lock(print_sem);
		write(1, msg, strlen(msg));
		unlock(print_sem);

    		for (int j = 0; j < 10; j++) {
        		if (sh->channel[j] == -1) {
        			sh->channel[j] = j;
           			sh->device[j] = req.id;
            			final_ch = j;
            			break;
        }
    }

	char msg1[120];

	sprintf(msg, "Manager: Channel %d reallocated to Device %d\n", final_ch, req.id);

	lock(print_sem);
	write(1, msg, strlen(msg));
	unlock(print_sem);
}

        unlock(semid);
    }

    close(fd[0]);

    for (int i = 0; i < DEVICES; i++) {
        wait(NULL);
    }

    write_log(sh->channel, sh->device);

    printf("\nLog file created\n");

    shmdt(sh);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    semctl(print_sem, 0, IPC_RMID);

    return 0;
}
