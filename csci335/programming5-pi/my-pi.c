#include "picalc.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc <= 2) {
        FATALERR(EXIT_FAILURE, "invalid number of arguments.");
    }

    int childc = atoi(argv[1]);
    int throwc = atoi(argv[2]);

    picalc_mc(childc, throwc);
}