#include <stdio.h>
#include "console.h"

void printfc(char *string, char *color) {
    if (color == NULL) {
        printf("%s", string);
        
        return;
    }
    
    printf("%s%s%s", color, string, RESET);
}