#include <stdio.h>
#include "freader.h"

int getlinec(char* search, char* filep, int mode) {
    // Open the file in read mode.
    FILE *file = fopen(filep, "r");

    // Whoops, it's null.
    if (file == NULL) {
        return -1;
    }

    // Build the pattern lookup table.
    char *plookup = calloc(1, sizeof(char) * ASCII_BOUNDS);
    int patc = -1;
    for (;search[++patc] != '\0';) {
        // Since we use calloc to allocate space for the lookup table, it's quicker to define 0 as NULL instead of iterating through setting each to -1.
        plookup[search[patc]] = patc + 1;
    }

    patc++;

    // Begin reading through the file line-by-line until the EOF.
    char *buffer = malloc(sizeof(char) * 255);
    int readc = 0;
    int linec = 0;
    int linen = 0;

    while ((readc = fgetsc(buffer, 255, file)) != -1) {
        linec += strlkp(plookup, search, buffer, patc - 1, readc - 1, mode);
    }

    fclose(file);
    return linec;
}

int strlkp(char *plookup, char *pattern, char *buffer, int patc, int bufc, int mode) {
    // This algorithm is derived from the Boyer-Moore fast pattern search algorithm.
    // Honestly, it might be a 1:1 copy. I just read about it on Wikipedia and drew it out. 
    // Also, this algorithm is really freaking cool. Sublinear speeds? Impressive. 
    // What's even cooler -- from what I understand, the larger the pattern the quicker the runtime. 

    // Anyways, onto the actual code. (Sorry about these comments, I'm exhausted. I'm sure I'll tell you all about this later.)
    int lbounds = 0;
    int ubounds = patc - 1; 

    // Loop while the upper bounds is less than the bufc. If we reach past our bounds, we know that we're done searching
    // through the string -- if you're past the bounds, it means there's not enough characters to match the pattern.
    while (ubounds < bufc) {
        // Determine the index of the 'bad' character -- eg: the last character (left -> right) that doesn't match the same index
        // of the pattern.
        int badi = ubounds;
        while (badi >= lbounds && chareql(pattern[badi - lbounds], buffer[badi], mode) == 1) {
            badi--;
        }

        // If badi is *lower* than the lower bounds, all characters match. This means we've found a match!
        if (badi < lbounds) {
            return 1;
        }

        // Now that we have the index of the 'bad' char, determine if that character in the buffer can be found in the pattern,
        // and if so, at what index.
        int plval = plookup[buffer[badi]];
        int shiftc = 0;

        // Since the plookup table is 1-indexed, we check to see if the val at badi is 0. 
        // If so, we set our shiftc to the len of the pattern.
        if (plval == 0) {
            shiftc = patc;
        }

        // Edge-case handing of when badi is somewhere in the middle of the pattern. In this instance, our valid plval indexes
        // will be from 0->badi. If so, set the shift to the size of the pattern.
        else if ((plval - 1) > (badi - lbounds)) {
            shiftc = patc;
        }

        // In all other cases, we add the index of the char.
        else {
            shiftc = (patc - plval);
        }

        // Add shiftc to the upper and lower bounds to continue advancing the search.
        lbounds += shiftc;
        ubounds += shiftc;
    }

    return 0;
}

int chareql(char first, char second, int mode) {
    // Convert both first and second tolower variants.
    if (mode == NOCASE_SENS) {
        first = tolower(first);
        second = tolower(second);
    }

    return (first == second);
}

int fgetsc(char *buffer, int bufc, FILE *file) {
    for (int i = 0; i < bufc; i++) {
        // Read the next char from the file and write it to index i of the buffer.
        buffer[i] = fgetc(file);

        // If the written char is an EOF, replace it with NULL and return i + 1.
        if (buffer[i] == EOF) {
            if (i == 0) {
                return -1;
            }

            buffer[i] = '\0';
            return i + 1;
        }

        // If the written char is a newline, add NULL to the next index, increment i and return.
        else if (buffer[i] == '\n') {
            buffer[++i] = '\0';
            return i + 1;
        }
    }
    return -1;
}