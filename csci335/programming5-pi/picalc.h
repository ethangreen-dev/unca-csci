#ifndef PICALC_H
#define PICALC_H

#include <stdlib.h>
#include <sys/sem.h>

#define FATALERR(err, f_, ...) fprintf(stderr, f_, ##__VA_ARGS__); exit(err)

struct hitc_shm {
    int sid;
    struct sembuf sbuf;
    unsigned long long int hitc;
};

void spawn(int throwc, int hit_id);

double picalc_mc(int childc, unsigned long long int throwc);
double rng_range(double min, double max);

#endif