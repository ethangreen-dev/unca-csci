#include "philosopher.h"
#include "semaphore_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main(int argc, char**argv){

    if (argc <= 1) {
        perror("Not enough arguments supplied.\n");
        exit(EXIT_FAILURE);
    }

    int target = strcmp("deadlock", argv[2]) ? CORRECTED : DEADLOCK;

    semaphore_init(); // initialize semaphorea
    create_5_philosophers(target);

    int wait_time = wait_time = atoi(argv[1]);

    printf("PARENT: sleeping for %i seconds\n", wait_time);
    sleep(wait_time);

    kill_5_philosophers();
    sleep(2);  // wait for the childen to die
    semaphore_destroy(); // cleanup all semaphores
    return 0;
}

