#include <stdio.h>
#include <string.h>

#include "freader.h"

int main(int argc, char **argv) {
    // We can't do anything if we only have two args.
    if (argc <= 2) {
        exit(1);
    }

    // These are the argument indexes if there is no additional argument at index 2.
    int pati = 1;
    int startfilei = 2;
    int mode = CASE_SENS;

    // If the third argument is -i, we need to set our mode to NOCASE_SENS and offset the rest of the argument 
    // starting indexes.
    if (strcmp(argv[1], "-i") == 0) {
        pati = 2;
        startfilei = 3;
        mode = NOCASE_SENS;
    }

    char *pattern = argv[pati];

    // Iterate through each subsequent listed file.
    for (int i = startfilei; i < argc; i++) {
        char *file = argv[i];
        int linec = getlinec(pattern, file, mode);

        if (linec == -1) {
            printf("file '%s' could not be opened.\n", file);
            continue;
        }

        printf("'%s' found in file '%s' on %d lines.\n", pattern, file, linec);
    }
}