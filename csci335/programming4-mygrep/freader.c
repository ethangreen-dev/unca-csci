#include <stdio.h>
#include "freader.h"

int getlinec(char* search, char* file, int mode) {
    
}

int strlkp(char *plookup, char *pattern, char *buffer, int patternlen, int bufferlen, int mode) {

}

int chareql(char first, char second, int mode) {
    if (mode == NOCASE_SENS) {
        first = tolower(first);
        second = tolower(second);
    }
}

int fgetsc(char *buffer, int bufc, FILE *file) {
    for (int i = 0; i < bufc; i++) {
        // Read the next char from the file and write it to index i of the buffer.
        buffer[i] = fgetc(file);

        // If the written char is an EOF, replace it with NULL and return i + 1.
        if (buffer[i] == EOF) {
            buffer[i] = '\0';
            return i + 1;
        }

        // If the written char is a newline, add NULL to the next index, increment i and return.
        else if (buffer[i] == '\n') {
            buffer[++i] = "\0";
            return i + 1;
        }
    }

    return -1;
}