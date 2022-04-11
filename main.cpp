#include <iostream>
#include "Lexer/main.h"

int main() {
    const char* sFile = "../Lexer/file.txt";
    FILE* fp = fopen(sFile,"r");
    if (fp == NULL) {
        printf("OPEN ERROR!\n");
        exit(-1);
    }
    extern FILE* yyin;
    yyin = fp;
    extern int yylex();
    int c;
    while(c=yylex()){
        printf("%d\n",c);
    }
    return 0;
}
