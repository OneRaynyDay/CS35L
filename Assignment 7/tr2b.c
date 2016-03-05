#include <stdio.h>
#include <stdlib.h>
#include "string.h"

void printError(char* str){
    fprintf(stderr, str);
}

void tr2b(char* str1, char* str2){
    char* output = malloc(sizeof(char) * 64);
    int outputSize = 0;
    int outputCapacity = 64;
    char charMap[256];
    int j = 0;
    int i;
    for(i = 0; i < 256; i++){
        charMap[i] = i;
    }
    while(str1[j] != 0){ //loop through first dict
        if(str2[j] == 0){
            printError("Incorrect formatting : Incorrect size of string.");
            return;
        }
        charMap[str1[j]] = str2[j];
        j++;
    }
    if(!(str1[j] == 0 && str2[j] == 0)){
        printError("Incorrect formatting : Incorrect size of string.");
        return;
    }
    i = 0;
    while(str1[i] != 0){
        int j = i;
        while(str1[j] != 0){
            if(i != j && str1[j] == str1[i]){
                printError("Incorrect formatting : duplicate bytes in from.");
                return;
            }
            j++;
        }
        i++;
    }
    
    int c = getchar();
    while(c != EOF){ //while the string is not null terminated
        putchar(charMap[c]);
        c = getchar();
    }
}

/* calls the function above */
int main(int argc,  char** argv){
    if(argc != 3){
        printError("Incorrect formatting : Incorrect number of arguments.");
        return 1;
    }
    tr2b(argv[1], argv[2]);
}
