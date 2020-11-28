#include "picalc.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

// Sorry about the amount of comments. I chugged an energy drink about 20 minutes ago and I can feel 
// my brain vibrating. I'm having too much fun right now (but that's because this is a fun assignment, 
// not because of the coffee).

// Calculate PI via the Monte Carlo method.
// Each child will "throw" a constant number of darts at a virtual 2x2 unit board. Within this board is a 
// circle of diameter 2 units, area pi. With the following rule we can approximate the value of PI.
// Darts in the circle / Total darts = PI / 4
double picalc_mc(int childc, unsigned long long throwc) {
    // Create a region of shared memory to be used by each child.
    int hitc_id = shmget(IPC_PRIVATE, sizeof(struct hitc_shm), IPC_CREAT | IPC_EXCL | 00666);
    
    // Attach to the shared memory so we can init the semaphor.
    struct hitc_shm *hitc = shmat(hitc_id, NULL, 0);
    hitc->hitc = 0;

    if (hitc == NULL) {
        FATALERR(EXIT_FAILURE, "failed to create %ld bytes of shared memory.\n", sizeof(struct hitc_shm));
    }

    // Init the semaphor.
    int semkey = time(NULL);
    int semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 00666);
    if (semid == -1) {
        FATALERR(EXIT_FAILURE, "failed to initialize semaphor.\n");
    }

    union semun {
        int val;
        struct semid_ds *buf;
        ushort *array;
    } argument;
    argument.val = 1;

    semctl(semid, 0, SETVAL, argument);

    hitc->sbuf.sem_num = 0;
    hitc->sbuf.sem_op = -1;
    hitc->sbuf.sem_flg = 0;

    hitc->sid = semid;

    // Since we have everything set up, initialize X number of worker processes.
    for (int i = 0; i < childc; i++) {
        if (fork() == 0) {
            spawn(throwc, hitc_id);
        }
    }

    while (wait(NULL) > 0);

    // Calculate the result.
    long double totalc = childc * throwc;
    long double est = ((long double)hitc->hitc / (long double)totalc) * 4.0;

    printf("PI: %Lf\n", est);
    return est;
}

// Spawn a new child. This child will throw X number of darts. The number of darts that hit the circle 
// will be written to shared memory. 
void spawn(int throwc, int hitc_id) {
    // Use this ridiculous datatype for the heck of it (and so we don't have to worry about weirdness with the shared counter).
    unsigned long long int count = 0;

    // Get access to shared memory.
    struct hitc_shm *hitc = shmat(hitc_id, 0, 0);

    // Seed the RNG with a value XOR'd from the time, a random val, and the pid of the process.
    // While the PID is guaranteed to be distinct, I added in extra stuff to be silly. 
    srand(rand() ^ time(NULL) ^ getpid());

    // Throw <throwc> darts at a virtual 2x2 board. If the dart lands within the circle of radius 1, increment the counter.
    for (unsigned long long int i = 0; i < throwc; i++) {
        double x = rng_range(-1.0, 1.0);
        double y = rng_range(-1.0, 1.0);

        double distance = (x * x) + (y * y);

        if (distance <= 1.0) {
            count++;
        }
    }

    // Lock the buffer. The SEM_UNDO flag will undo all changes made to this semaphor when the process exits.
    // hitc->sbuf is preinitted to lock the semaphor, so we can use it to make things quicker.
    semop(hitc->sid, &hitc->sbuf, SEM_UNDO);

    // Once we have lock, add our local count to the shared memory.
    hitc->hitc += count;

    // Upon exit the semop operation will reverse and the semaphor will be unlocked.
    exit(EXIT_SUCCESS);
}

double rng_range(double min, double max) {
    return rand() / ((double)RAND_MAX + 1) * 2.0 - 1.0;
}