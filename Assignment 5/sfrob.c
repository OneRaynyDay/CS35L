#include <stdio.h>
#include <stdlib.h>

int frobcmp(const void* arra, const void* arrb){
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

void sfrob(){
    //We are attempting to create a 2D array(array of c-string words)
    //and sorting it.
    char * * words = (char * *) malloc(0);
    int words_size = 0;
    char * curWord = (char *) malloc(0);
    int curWord_size = 0;
    char prevChar = ' ';
    char curChar = ' ';
    //read from stdin
    while(!feof(stdin)){
        //this is the current char
        curChar = getchar();
        if(prevChar == ' ' && curChar == ' ')
            continue;
        curWord = realloc(curWord, (++curWord_size) * sizeof(char));
        /*int breakflag = curChar; 
        if(breakflag == EOF) { 
            printf("breaking out now.");
            break;
        }  */ 
        if(curChar == ' '){ //space flag
            //make it into a word with the space
            curWord[curWord_size-1] = ' ';
            //flush it into words
            //increment words
            words_size++;
            words = realloc(words, words_size*sizeof(char*));
            words[words_size-1] = curWord;
            //empty out curWord for the next word
            //let's do a debug print:
            curWord = (char *) malloc(0);   
            curWord_size = 0; 
        }
        else{
            //remember to ^'*' the curChar here
            curWord[curWord_size-1] = curChar; //frobnicated here
        }
        if(((int)curChar) != EOF)
            prevChar = curChar;
    }   
    //flushing out the last bits [Only if the previous word was not a space]
    if(prevChar != ' '){
        //printf("flushing it out, the last 2 chars %c, %c" , prevChar, curChar);
        curWord[curWord_size-1] = ' ';
        words_size++;
        words = realloc(words, words_size*sizeof(char*));
        words[words_size-1] = curWord;
    }
    qsort(words, words_size, sizeof(char*), frobcmp);
    if(words_size == 1 && curWord_size == 1 && curWord[curWord_size-1] == ' '){ free(words); return; }
    //printf("Finished. number of words: %d", words_size);
    for(int i = 0; i < words_size; i++){
        int ctr = 0;
        while(words[i][ctr] != ' '){
           putchar(words[i][ctr++]);
        }
        putchar(' ');
    }
    free(words);
}

int main(){
    sfrob();
    
}
