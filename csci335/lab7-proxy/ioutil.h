#ifndef IOUTIL_H
#define IOUTIL_H

#include <stdio.h>

#define DEBUG 1

#define ERRPRNT(f_, ...) printf("[!] ERROR: "); printf(f_, ##__VA_ARGS__);
#define DBGPRNT(f_, ...) if (DEBUG) { printf("[?] "); printf(f_, ##__VA_ARGS__); }
#define INFPRNT(f_, ...) printf("[#] "); printf(f_, ##__VA_ARGS__);

#endif