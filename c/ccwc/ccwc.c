/*
 * Coding Challenge #1 - Build Your Own wc Tool
 * More info at https://codingchallenges.fyi/challenges/challenge-wc/
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <ctype.h>
#include <wchar.h>
#include <errno.h>
#include <locale.h>

enum mode_t { BYTE, CHARACTER, WORD, LINE };

FILE* open_file(const char* filename, const char* opt){
    FILE* file = fopen(filename, opt);
    if(file == NULL){
        fprintf(stderr, "File does not exist\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

void count_byte(FILE* file){
    uint64_t count = 0;
    while(fgetc(file) != EOF){
        count++;
    }
    printf("%lu ", count);
}

void count_line(FILE* file){
    uint64_t count = 0;
    char buffer[256];
    while(fgets(buffer, 256, file) != NULL){
        count++;
    }
    printf("%lu ", count);
}

void count_word(FILE* file){
    uint64_t count = 0;
    char c = fgetc(file);
    int isWord = 0;
    do{
        if(!isspace(c) && !isWord){
            isWord = 1;
        }
        if(isspace(c) && isWord){
            count++;
            isWord = 0;
        }
        c = fgetc(file);
    }while(c != EOF);    

    printf("%lu ", count);
}

void count_char(FILE* file){
    uint64_t count = 0;
    wint_t c;
    while((c = fgetwc(file)) != WEOF){
        count++;
    }
    if(EILSEQ == errno){
        printf("weird\n");
    }

    printf("%lu ", count);
}

void no_opt(FILE* file){
    count_line(file);
    rewind(file);
    count_word(file);
    rewind(file);
    count_byte(file);
}

void stdin_no_opt(){
    int64_t lineCount = 0, wordCount = 0, byteCount = 0;
    int c;
    int isWord = 0;
    while((c = fgetc(stdin)) != EOF){
        byteCount++;
        if(!isspace(c) && !isWord){
            isWord = 1;
        }
        if(isspace(c) && isWord){
            wordCount++;
            isWord = 0;
        }
        if(c == '\n'){
            lineCount++;
        }
    }
    printf("%lu %lu %lu\n", lineCount, wordCount, byteCount);
}

void from_std_in(void(*fptr)(FILE*), int opt){
    if(opt == -1) {
       return stdin_no_opt();
    }
    fptr(stdin);
    printf("\n");
}

int main(int argc, char* argv[]){
    setlocale(LC_CTYPE, "");

    mode_t mode; 
    int opt = getopt(argc, argv, "clwm");  
        
    void (*fptr)(FILE*);
    
    switch(opt){
        case 'c': fptr = &count_byte; break;
        case 'l': fptr = &count_line;  break;
        case 'w': fptr = &count_word; break;
        case 'm': fptr = &count_char; break;
        case -1 : fptr = &no_opt; break; 
        default:
            fprintf(stderr, "Usage: %s [-c] <file>\n", argv[0]);
            exit(EXIT_FAILURE); 
    }

    if(optind == argc || argv[1] == "-"){
       from_std_in(fptr, opt);
    }else{ 
    char* filename = argv[optind];
    FILE* file = open_file(filename, "r");
    
    fptr(file); 
    printf("%s\n", filename);
    }

    return 0;
}
