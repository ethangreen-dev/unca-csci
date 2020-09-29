#include "shelper.h"

// A helper function that determines whether a string is smaller than another.
int smaller_than(char *string1, char *string2) {
    int i = 0;
    
    // Iterate until we reach a point where the two strings DO NOT equal each other.
    while (string1[i] == string2[i]) {
        i++;
    }
    
    // If either of the strings is null, we know it is smaller.
    if (string1[i] == '\0') {
        return 1;
    }
    
    if (string2[i] == '\0') {
        return 0;
    }
    
    return string1[i] < string2[i];
}