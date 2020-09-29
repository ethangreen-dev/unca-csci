#include "secret_words.h"
#include <stdlib.h>
#include <stdio.h>

char secret_word_0[] = "Captain";
char secret_word_1[] = "Ahab";
char secret_word_2[] = "the";
char secret_word_3[] = "first";
char secret_word_4[] = "American"; // FIXED: Added secret word after found with Ghidra. 

int number_of_secret_words(){
    return 5;
}

char * get_secret_word(int i){
    if(i == 0) return secret_word_0;
    if(i == 1) return secret_word_1;
    if(i == 2) return secret_word_2;
    if(i == 3) return secret_word_3;
    if(i == 4) return secret_word_4; // FIXED: Added if statement for secret_word_4.
    printf("Error, get_secret_word(%i) called, > max # secret words\n",i);
    exit(1);
}
