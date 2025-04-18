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
#include <string.h>
#include <regex.h>

#define BYTE_OPT 0x01
#define LINE_OPT 0x02
#define WORD_OPT 0x04
#define CHAR_OPT 0x08
#define TOTAL_OPT 5

struct count_t{
    uint64_t byte;
    uint64_t line;
    uint64_t word;
    uint64_t character;
}count_t;

FILE* open_file(const char* filename, const char* opt){
    FILE* file = fopen(filename, opt);
    if(file == NULL){
        fprintf(stderr, "File does not exist\n");
        exit(EXIT_FAILURE);
    }
    return file;
}

void count_char(FILE* file, struct count_t* count){
    wint_t c;
    while((c = fgetwc(file)) != WEOF){
        count->character++;
    }
}

void get_file_counts(FILE* file, struct count_t* count, char opt){ 
    wchar_t c;
    int isWord = 0;
    while((c = fgetwc(file)) != EOF){
        count->byte++;
        if(!isspace(c) && !isWord){
            isWord = 1;
        }
        if(isspace(c) && isWord){
            count->word++;
            isWord = 0;
        }
        if(c == '\n'){
            count->line++;
        }
    }
}

int main(int argc, char* argv[]){
    setlocale(LC_CTYPE, "");

    char opt = 0x00;

    char options[TOTAL_OPT] = { '\0' };

    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            strcpy(options, argv[i]);
        }
    }    

    for(int i = 1; options[i] != '\0'; i++){
        if(options[i] == 'c') opt |= BYTE_OPT;
        if(options[i] == 'l') opt |= LINE_OPT;
        if(options[i] == 'w') opt |= WORD_OPT;
        if(options[i] == 'm') opt |= CHAR_OPT;
    }

    if(options[0] == '\0'){
        opt |= BYTE_OPT | LINE_OPT | WORD_OPT;
    }

    char filename[256];
    filename[0] = '\0';
    for(int i = 1; i < argc; i++){
        if(argv[i][0] != '-'){
            strcpy(filename, argv[i]);
        }
    } 

    FILE* file = filename[0] == '\0' ? stdin : fopen(filename, "r");

    struct count_t count;
    count.word = 0;
    count.byte = 0;
    count.line = 0;
    count.character = 0;

    get_file_counts(file, &count, opt);
        
    if(opt & LINE_OPT){
        printf("%lu ", count.line);
    }
    if(opt & WORD_OPT){
        printf("%lu ", count.word);
    } 
    if(opt & CHAR_OPT){
        printf("%lu ", count.character);
    }
    if(opt & BYTE_OPT){
        printf("%lu ", count.byte);
    }
    if(filename[0] != '\0'){
        printf("%s", filename);
    }
    printf("\n");

    return 0;
}
