#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int count = 0;

int frobcmp(const void* arra, const void* arrb){
    count++;
    int ctr = 0;
    const char * a = *(const char **) arra; //cast
    const char * b = *(const char **) arrb; //cast
    // then we know cmp is still 0, continue to check in parallel:
    while(a[ctr] != ' '){
        char froba = (char)(a[ctr]^'*');
        char frobb = (char)(b[ctr]^'*');
        if(froba-frobb == 0){
            ctr++;
            continue;
        }
        return froba-frobb;
    } 
    ctr = 0;
    while(a[ctr] != ' ' && b[ctr] != ' '){
        if(a[ctr] == ' ' && b[ctr] != ' '){
            return 1;
        }        
        if(b[ctr] == ' ' && a[ctr] != ' '){
            return -1;
        }
        ctr++;
    }    
    return 0; // if it never goes into the while loop, means both are empty!
}

void sfrob(int initSize){
    //We are attempting to create a 2D array(array of c-string words)
    //and sorting it.

    char * * words = (char * *) malloc(1 * sizeof(char *));
    int words_size = 1;
    char * curWord = (char *) malloc(initSize * sizeof(char));
    int curWord_capacity = initSize;
    int curWord_size = 0;
    char prevChar = ' ';
    char curChar;
    curChar = '#';//placeholder
    //read from stdin
    words[0] = curWord;

    while(read(0, &curChar, sizeof(char)) > 0){
        if(curWord_size == curWord_capacity){
            curWord = (char *) realloc(curWord, ++curWord_capacity * sizeof(char));
        }
        curWord[curWord_size++] = curChar;
    }    
    if(curWord[curWord_size-1] != ' '){
        //add a space
        curWord = (char *) realloc(curWord, ++curWord_capacity * sizeof(char));
        curWord[curWord_size] = ' ';
    }
    for(int i = 0; i < curWord_size; i++){
        if(curWord[i] == ' '){
            words_size++;
            words = realloc(words, words_size * sizeof(char *));
            words[words_size-1] = curWord + i + 1;
        }
    }
    qsort(words, words_size, sizeof(char*), frobcmp);
    
    if(words_size == 1 && curWord_size == 1 && curWord[curWord_size-1] == ' '){ 
        free(words); 
        free(curWord);
        return; 
    }

    char minibuffer[1];
    for(int i = 0; i < words_size; i++){
        int ctr = 0;
        while(words[i][ctr] != ' '){
           minibuffer[0] = words[i][ctr++];
           write(1, minibuffer, sizeof(char));
        }
        minibuffer[0] = ' ';
        write(1, minibuffer, sizeof(char));
    }
    free(words);
    free(curWord);
    fprintf(stderr, "Comparisons: %d", count);
}

int main(){
    struct stat fileStat;
    if(fstat(0,&fileStat) < 0)    
        return 1;
    if(S_ISREG(fileStat.st_mode)){
        sfrob(fileStat.st_size);
    }
    else{
        sfrob(1*sizeof(char *));
    }
}
