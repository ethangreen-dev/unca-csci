#include "semaphore_lib.h"
#include "philosopher.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int chopsticks[5];
pid_t philosopher_pid[5];

int eat_count = 0;
int think_count = 0;

int pickup_chopstick(int which_stick){
    // try to pick up chopstick 'which_stick' [0-4]
    pid_t pid = getpid();
    printf("Child[%i] pickup_chopstick(%i)\n",pid,which_stick);
    fflush(stdout);
    usleep(10000); // 0.1 seconds?
    return semaphore_lock(which_stick);
}

int setdown_chopstick(int which_stick){
    pid_t pid = getpid();
    printf("Child[%i] pickup_chopstick(%i)\n",pid,which_stick);
    fflush(stdout);
    usleep(10000);
    return semaphore_unlock(which_stick);
}

void eat_from_plate(){
    pid_t pid = getpid();
    printf("Child[%i] eating\n",pid);
    fflush(stdout);
    eat_count++;
    sleep(1);
}

void think(){
    pid_t pid = getpid();
    printf("Child[%i] thinking\n",pid);
    fflush(stdout);
    think_count++;
    sleep(1);
}


void sigterm_handler(int sig_num){
    pid_t mypid = getpid();
    printf("Child[%i] eat_count=%i think_count=%i\n",mypid, eat_count, think_count);
    fflush(stdout);
    exit(0);
}


void sigchild_handler(int sig_num){
    int status;
    pid_t pid;
    while((pid = waitpid(-1, &status, WNOHANG|WCONTINUED)) > 0){
        printf("Child %i exited with status %i\n",pid, status);
    }
}


void create_5_philosophers(int target){
    // initialize chopsticks
    int i;
    for(i=0;i<5;i++){
        chopsticks[i] = create_semaphore(i);
    }
    // set sigterm handler
    if( signal(SIGTERM, sigterm_handler) == SIG_ERR){
        printf("Error setting SIGTERM handler\n");
        exit(1);
    }
    // create 5 philosophers processes 
    for(i=0;i<5;i++){
        pid_t temp = fork();
        if (temp == 0){
            if (target == DEADLOCK) {
                philosopher_algorithm(i);
            }

            optimized_algorithm(i);

            exit(0);
        }else{
            philosopher_pid[i] = temp;
        }
    }
    if( signal(SIGCHLD, sigchild_handler) == SIG_ERR){
        printf("Error setting SIGCHLD handler\n");
    }
}

void kill_5_philosophers(){
    int i;
    for(i=0;i<5;i++){
        printf("Sending SIGTERM to child %i\n", philosopher_pid[i]);
        kill( philosopher_pid[i], SIGTERM);
    }
}

// This is a lazy implementation of Dijkstra's Resource Hierarchy solution to his Dinish Philosophers thought experiment.
// While not the most optimized, the simplicity of the implementation is the most attractive component.
//
// This algorithm is extremely similiar to the deadlocking implementation below, but instead of strictly selecting
// in left->right order, we're instead going to pick up chopsticks in smaller->larger order.
void optimized_algorithm(int num) {
    // Check to see if we're at the end of the philosopher array. +1 because when assigned, num is 0-indexed.
    int rule = num + 1 == 5;

    // The resource hierarchy solution describes a solution similar to below, but instead of picking up
    // chopsticks left to right, we pick up smallest to largest.
    int smaller = chopsticks[rule ? (num + 1) % 5 : num];
    int larger = chopsticks[rule ? num : (num + 1) % 5];

    pid_t pid = getpid();
    printf("Child[%i] starting philosopher_algorithm(%i)\n",pid,num);
    fflush(stdout);

    while (1) {
        pickup_chopstick(smaller);
        pickup_chopstick(larger);

        eat_from_plate();

        setdown_chopstick(larger);
        setdown_chopstick(smaller);

        think();
    }
}

void philosopher_algorithm(int num){
    int chopstick1 = chopsticks[num];
    int chopstick2 = chopsticks[(num+1)%5];

    pid_t pid = getpid();
    printf("Child[%i] starting philosopher_algorithm(%i)\n",pid,num);
    fflush(stdout);

    while(1){ // basic algorithm
        pickup_chopstick( chopstick1 );
        pickup_chopstick( chopstick2 );
        eat_from_plate();
        setdown_chopstick( chopstick1 );
        setdown_chopstick( chopstick2 );
        think();
    }
}









