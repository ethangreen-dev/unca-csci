#include <stdio.h>

#include "freader.h"

int main() {
    char *pattern = "the";
    char *file = "moby.txt";

    int linec = getlinec(pattern, file, NOCASE_SENS);

    printf("'%s' found in file '%s' on %d lines.\n", pattern, file, linec);
}