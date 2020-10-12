#ifndef FREADER_H
#define FREADER_H

#define CASE_SENS 1
#define NOCASE_SENS 0
#define ASCII_BOUNDS 127

#include <stdio.h>

// Return the number of lines in the file which the pattern can be found.
// _mode_ is determined by CASE_SENS or NOCASE_SENS.
int getlinec(char* search, char* file, int mode);

// Quick string lookup function, based on the Boyer-Moore algorithm.
int strlkp(char *plookup, char *pattern, char *buffer, int patc, int bufc, int mode);

// Determine if two chars are equal, follows CASE_SENS and NOCASE_SENS mode rules.
int chareql(char first, char second, int mode);

// Read in X chars from the start of a line to the newline, inclusive. 
// This function will return the number of characters written to the buffer starting at index 0, to the newline (inclusive).
int fgetsc(char *buffer, int bufc, FILE *file);

#endif